set(src AccPlatform.cpp)
add_library(tlm_platform STATIC ${src})

set(lib_list tlm_platform
             pool_engine
	     lock_engine
             dma_engine
             reg_group
             memory
             reg_ctl
             common_lib)

if(${USE_HALF_FLOAT})
  set(lib_list ${lib_list} "${LLVM_HOME}/lib/clang/6.0.1/lib/linux/libclang_rt.builtins-x86_64.a")
endif(${USE_HALF_FLOAT})

FUNCTION(build_exe target_name output_name src_ref extra_lib)
	if(${extra_lib})
		set(libs ${${extra_lib}})
	else()
		set(libs "")
	endif()

	add_executable(${target_name} ${${src_ref}})
	target_link_libraries(${target_name}
	                      ${libs}
	                      ${lib_list}
	                      ${SYSTEMC_LIB64_DIR} ${SYSTEMC_LIBRARIES}
	                      ${SCML_LIB64_DIR} ${SCML_LIBRARIES})
	set_target_properties(${target_name} PROPERTIES SUFFIX ".out")
	if(NOT ${output_name} STREQUAL "")
		set_target_properties(${target_name} PROPERTIES OUTPUT_NAME "${output_name}")
	endif()
ENDFUNCTION(build_exe)

# =================== ArchC Test Platform =========================
include_directories(${ARCHC_INCLUDE64_DIR})

set(isa_sim_src ISASimPlatform.cpp
                ISASimTest.cpp)

set(archc_lib isasim ${ARCHC_LIB64_DIR} ${ARCHC_LIBRARIES})

build_exe(isasimtest platform isa_sim_src archc_lib)
