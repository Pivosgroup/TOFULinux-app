SRCS=ConsoleDeviceKitPowerSyscall.cpp \
     ConsoleUPowerSyscall.cpp \
     UPowerSyscall.cpp \
     LogindUPowerSyscall.cpp \
     AMLPowerSyscall.cpp

LIB=powermanagement_linux.a

include ../../../Makefile.include
-include $(patsubst %.cpp,%.P,$(patsubst %.c,%.P,$(SRCS)))
