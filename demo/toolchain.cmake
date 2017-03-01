
set(CMAKE_SYSTEM_NAME "Generic")

find_program(AVR_CC avr-gcc)
find_program(AVR_OBJCOPY avr-objcopy)
find_program(AVR_SIZE_TOOL avr-size)
find_program(AVR_OBJDUMP avr-objdump)

if ((DEFINED ENV{CC}))
  SET(CMAKE_C_COMPILER $ENV{CC})
else()
  SET(CMAKE_C_COMPILER ${AVR_CC})
endif()

SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ffunction-sections -fdata-sections")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--gc-sections")
