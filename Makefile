# Default goal
.DEFAULT_GOAL := help

# Some variables
QMK_HOME 	:= $(shell qmk config user.qmk_home | cut -d= -f2)
KEYBOARD 	:= gmmk/gmmk2/p96/iso
KEYMAP   	:= custom
SRC_FOLDER 	:= ./keymaps/${KEYMAP}
DEST_FOLDER := ${QMK_HOME}/keyboards/${KEYBOARD}/keymaps/${KEYMAP}

# List all files in the source folder
FILES := $(wildcard $(SRC_FOLDER)/*)

# Set `USE_DOCKER=1` to use Docker for building
ifeq (${USE_DOCKER},1)
	MAKE := ./util/docker_build.sh
else
	MAKE := make
endif

# Rule to get help about building the project
help:
	@echo "Use 'make build' to compile the firmware and 'make flash' afterwards."
	@echo "'make clean' - to clean the QMK firmware project ($(QMK_HOME))"

# Rule to compile the firmware
build: copy_files
	cd ${QMK_HOME} && ${MAKE} ${KEYBOARD}:${KEYMAP}

# Rule to copy files
copy_files: 
	@echo "Creating destination folder: $(DEST_FOLDER)"
	@mkdir -p $(DEST_FOLDER)
	@echo "Copying files from $(SRC_FOLDER) to $(DEST_FOLDER)"
	@cp $(FILES) $(DEST_FOLDER)
	@echo "Copy completed successfully"

# Rule to flash the compiled firmware
flash:
	cd ${QMK_HOME} && ${MAKE} ${KEYBOARD}:${KEYMAP}:flash

# Rule to delete the destination folder
clean:
	@echo "Deleting destination folder: $(DEST_FOLDER)"
	@rm -rf $(DEST_FOLDER)
	@echo "Deletion completed successfully"

# Phony targets to avoid conflicts with actual file names
.PHONY: clean build flash copy_files help $(DEST_FOLDER)