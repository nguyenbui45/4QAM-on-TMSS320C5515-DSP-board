################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C5500 Compiler'
	"D:/CCS/ccsv8/tools/compiler/c5500_4.4.1/bin/cl55" -v5515 --memory_model=large -g --include_path="C:/Users/COMPUTER/workspace_v8/QU_AM" --include_path="D:/CCS/ccsv8/tools/compiler/c5500_4.4.1/include" --define=c5515 --display_error_number --diag_warning=225 --ptrdiff_size=16 --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


