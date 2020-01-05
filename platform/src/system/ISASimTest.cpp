#include <systemc>
#include "ISASimPlatform.h"
#include "AccPlatform.h"
#include "tclap/CmdLine.h"

const char *project_name="riscv";
const char *project_file="riscv.ac";
const char *archc_version="2.4.1";
const char *archc_options="-abi ";

std::string concat(std::string s, int n) {
  return s + std::to_string(n);
}

size_t split(const std::string &txt, std::vector<std::string> &strs, char ch = ' ') {
  size_t pos = txt.find( ch );
  size_t initialPos = 0;
  strs.clear();

  // Decompose statement
  while( pos != std::string::npos ) {
    strs.push_back( txt.substr( initialPos, pos - initialPos ) );
    initialPos = pos + 1;

    pos = txt.find( ch, initialPos );
}

// Add the last one
strs.push_back( txt.substr( initialPos, std::min( pos, txt.size() ) - initialPos + 1 ) );
  return strs.size();
}

char** new_app_argv(int app_argc, const std::vector<std::string> &split_app_argv) {
  char** app_argv_cstr_array = new char*[app_argc];
  for (unsigned int i = 0; i<app_argc; i++ ) {
    std::string str = split_app_argv[i];
    char* arg = new char[str.size()+1];
    strcpy(arg, str.c_str());
    app_argv_cstr_array[i] = arg;
  }
  return app_argv_cstr_array;
}

void delete_app_argv(int app_argc, char** app_argv_cstr_array) {
  for (unsigned int i = 0; i<app_argc; i++ ) {
    delete app_argv_cstr_array[i];
  }
  delete [] app_argv_cstr_array;
}

int sc_main(int ac, char* av[]) {
  std::string app_argv;
  bool gdb_enable; 
  std::string filib_argv;
  try {
    TCLAP::CmdLine cmd("Triple-core ArchC RISC-V Fault Simulation Platform", ' ', "0.0.0.0");
    TCLAP::ValueArg<std::string> app_argv_arg
    ( "a", "app", "Input application command line arguments argv (enclose string including space with quotes)", 
				true, "./binary", "string", cmd);
    TCLAP::SwitchArg gdb_enable_arg
      ( "g","gdb","To enable gdb support for ArchC RISC-V processor", cmd, false);

    cmd.parse(ac, av);
    app_argv = app_argv_arg.getValue();
    gdb_enable = gdb_enable_arg.getValue();
                
  }
  catch (TCLAP::ArgException &e) //catch any exceptions
  {
    std::cerr<< "error: " << e.error() << " for argument " << e.argId() << std::endl;
    exit(-1);
  }

  std::vector<std::string> split_app_argv;
  size_t app_argc = split(app_argv, split_app_argv); 
  char** app_argv_cstr_array = new_app_argv(app_argc, split_app_argv);

  std::vector<std::string> split_filib_argv;

  const int NCORE = 4;
  sc_set_time_resolution(1, SC_NS);
  AccPlatform acc_platform("AcceleratorPlatform");
  ISASimPlatform *platform[NCORE];
  for (int i = 0; i < NCORE; ++i)
    platform[i] = new ISASimPlatform(concat("Controller", i).c_str());

  /* Bus Binding */
  for (int i = 0; i < NCORE; ++i) {
    platform[i]->ctrler_local_t_adapter(acc_platform.local_bus);
    platform[i]->ctrler_global_t_adapter(acc_platform.system_bus);
  }

  for (int i = 0; i < NCORE; ++i) {
    platform[i]->controller.cpu.set_args(app_argc, app_argv_cstr_array);
    platform[i]->controller.cpu.load(app_argv_cstr_array[0]);
    platform[i]->controller.cpu.init();
  }

  delete_app_argv(app_argc, app_argv_cstr_array);
	
  cerr << endl;

#ifdef AC_DEBUG
  ac_trace("controller.trace");
#endif

  sc_start();

  for (int i = 0; i < NCORE; ++i) 
	platform[i]->controller.cpu.PrintStat();
  cerr << endl;

#ifdef AC_STATS
  ac_stats_base::print_all_stats(std::cerr);
#endif

#ifdef AC_DEBUG
  ac_close_trace();
#endif

  cout << "= " << sc_time_stamp().to_string() << " =\n"
       << "Finished sc_main." << endl;

  return platform[0]->controller.cpu.ac_exit_status;
}
