# ##### UTILITIES ##### #
CROSS_COMPILE = arm-none-eabi
AS = ${CROSS_COMPILE}-gcc
AR = ${CROSS_COMPILE}-ar
CC = ${CROSS_COMPILE}-gcc
CXX = ${CROSS_COMPILE}-g++
LD = ${CROSS_COMPILE}-gcc
AXF2BIN = ${CROSS_COMPILE}-objcopy
SIZE = ${CROSS_COMPILE}-size
#UPLOAD = tools/artemis/linux/artemis_svl
UPLOAD = tools/artemis/artemis_svl.py

# ##### CONFIGURATION ##### #
TARGET_NAME = Apollo3Artemis
VARIANT = redboard_artemis_nano
CORE = arduino
MCU = apollo3
CPU = cortex-m4
FPU = fpv4-sp-d16
FABI = hard

# ##### SERIAL PORT ##### #
SERIAL_PORT = /dev/ttyUSB0
BAUD_RATE = 115200
BAUD_RATE = 230400
BAUD_RATE = 460800

# ##### BUILD FLAGS ##### #
INCLUDE =

DEFINES =
DEFINES += -DF_CPU=48000000L
DEFINES += -DARDUINO=1812
DEFINES += -DARDUINO_ARCH_APOLLO3
DEFINES += -DPART_apollo3

COMMON_CXX_C_S_FLAGS = -c -g -MMD -mcpu=${CPU} -mthumb
COMMON_CXX_C_FLAGS = -mcpu=${CPU} -mthumb -mfloat-abi=${FABI} -fdata-sections -Os
CXXFLAGS = ${COMMON_CXX_C_S_FLAGS} ${COMMON_CXX_C_FLAGS} -ffunction-sections -std=gnu++11 -fno-threadsafe-statics -nostdlib --param max-inline-insns-single=500 -fno-rtti -fno-exceptions
CFLAGS = ${COMMON_CXX_C_S_FLAGS} ${COMMON_CXX_C_FLAGS} --function-sections -mfpu=fpv4-sp-d16 -std=gnu11
ASMFLAGS = ${COMMON_CXX_C_S_FLAGS} -x assembler-with-cpp

LDFLAGS =
LDFLAGS += -mthumb -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard
LDFLAGS += -static
LDFLAGS += -Wl,--gc-sections,--entry,Reset_Handler -Wl,--start-group -lm -lc -lgcc -Wl,--end-group
LDFLAGS += -Wl,-Map,${TARGET_NAME}.map
LDFLAGS += -fno-exceptions --specs=nano.specs -t -lstdc++ -lc -lnosys -lm
LDFLAGS += -nostdlib

ARFLAGS =
ARGLAGS += rcs

AXFFLAGS =
AXFFLAGS += -O binary

# ##### SOURCES ##### #
SOURCES =
#SUBDIRS = variants/${VARIANT} cores/${CORE}/am_sdk_ap3/ cores/${CORE}/ard_sup/ FreeRTOSv10.1.1/ exactle/ble-host/ exactle/ble-profiles/ exactle/wsf/ libraries/ payload/
SUBDIRS = variants/${VARIANT} cores/${CORE}/am_sdk_ap3/  cores/${CORE}/ard_sup/ FreeRTOSv10.1.1/ payload/

$(foreach SUBDIR,${SUBDIRS},					\
	$(eval include ${SUBDIR}/Makefile.include))

SOURCES_ASM = $(filter %.s,${SOURCES})
SOURCES_C = $(filter %.c,$(SOURCES))
SOURCES_CXX = $(filter %.cpp,$(SOURCES))

OBJS_ASM = $(SOURCES_ASM:%.s=%.o)
OBJS_C = $(SOURCES_C:%.c=%.o)
OBJS_CXX = $(SOURCES_CXX:%.cpp=%.o)

OBJS = ${OBJS_ASM} ${OBJS_C} ${OBJS_CXX}

all: ${TARGET_NAME}.bin

${TARGET_NAME}.bin: hal ${OBJS}
	${LD} ${OBJS_C} ${OBJS_CXX} ${LDFLAGS} -o ${TARGET_NAME}.axf
	${AXF2BIN} ${AXFFLAGS} ${TARGET_NAME}.axf ${TARGET_NAME}.bin
	${SIZE} -A ${TARGET_NAME}.axf

upload: ${TARGET_NAME}.bin
	if [ ! -r ${SERIAL_PORT} ]; then  sudo chmod a+r ${SERIAL_PORT} ; fi
	if [ ! -w ${SERIAL_PORT} ]; then  sudo chmod a+w ${SERIAL_PORT} ; fi
	${UPLOAD} ${SERIAL_PORT} -f ${TARGET_NAME}.bin -b ${BAUD_RATE};

hal:
	make -C ${HAL}

%.o: %.s
	echo "Building $<"
	${AS} ${ASMFLAGS} ${DEFINES} ${INCLUDE} $< -o $@

%.o: %.c
	echo "Building $<"
	${CC} ${CFLAGS} ${DEFINES} ${INCLUDE} $< -o $@

%.o: %.cpp
	echo "Building $<"
	${CXX} ${CXXFLAGS} ${DEFINES} ${INCLUDE}  $< -o $@

clean:
	rm -rf ${OBJS_C} ${OBJS_CXX}
	rm -rf ${TARGET_NAME}.axf ${TARGET_NAME}.map
