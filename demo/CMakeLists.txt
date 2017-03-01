cmake_minimum_required(VERSION 3.0)

project(unabto-arduino)
set(UNABTO_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/../unabto)
include(${UNABTO_ROOT}/build/cmake/unabto_files.cmake)

set(src_dir
  ${CMAKE_CURRENT_SOURCE_DIR}/src
  )

set(platform_dir
  ${CMAKE_CURRENT_SOURCE_DIR}/../arduino_platform
  )

set(src
  ${unabto_core_src}
  ${unabto_module_dns_client_src}
  ${unabto_module_dhcp_client_src}
  ${unabto_module_crypto_generic_src}
  ${unabto_module_network_w5100_src}
  ${unabto_device_driver_w5100_src}

  ${src_dir}/main.c
  ${platform_dir}/arduino_time.c
  ${platform_dir}/unabto_platform.c
  ${platform_dir}/spi.c
  )

include_directories(${unabto_core_include_directories})
include_directories(${src_dir})
include_directories(${platform_dir})

add_definitions(-DF_CPU=16000000L)
add_definitions(-Os)
add_definitions(-Wall)


#add_definitions(-DUNO)
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mmcu=atmega328p")

if (${BOARD} MATCHES "MEGA")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mmcu=atmega2560")
  add_definitions(-DMEGA)
elseif(BOARD MATCHES "UNO")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mmcu=atmega2560")
  add_definitions(-DUNO)
else()
  message(ERROR "You must specify a target board with -DBOARD=(MEGA|UNO)")
endif()



add_executable(main.elf ${src})

target_link_libraries(main.elf)


add_custom_command(OUTPUT main.hex 
  COMMAND avr-objcopy -O ihex -R .eeprom main.elf main.hex 
  DEPENDS main.elf)
add_custom_target(bin ALL DEPENDS main.hex) 
