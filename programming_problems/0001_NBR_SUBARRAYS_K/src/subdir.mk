
# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
./main_test.cpp \
./nbr_subarrays_k.cpp 

OBJS += \
./main_test.o \
./nbr_subarrays_k.o

CPP_DEPS += \
./main_test.d \
./nbr_subarrays_k.d


# Each subdirectory must supply rules for building sources it contributes
./main_test.o: ./main_test.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I./ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

./nbr_subarrays_k.o: ./nbr_subarrays_k.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I./ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


