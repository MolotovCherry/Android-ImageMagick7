ifeq ($(STATIC_BUILD),true)
    $(info [ Doing static build ])
    $(info )
else
    $(info [ Doing shared library build ])
    $(info )
endif


ifeq ($(HDRI_ENABLE),true)
    $(info [ HDRI enabled ])

    APP_CFLAGS += \
        -DMAGICKCORE_HDRI_ENABLE=1
    APP_CPPFLAGS += \
        -DMAGICKCORE_HDRI_ENABLE=1
endif

$(info [ Quantum depth: $(QUANTUM_DEPTH) ])
$(info )
APP_CFLAGS += \
    -DMAGICKCORE_QUANTUM_DEPTH=$(QUANTUM_DEPTH)
APP_CPPFLAGS += \
    -DMAGICKCORE_QUANTUM_DEPTH=$(QUANTUM_DEPTH)


# Add OpenMP flags if using OpenMP build
ifeq ($(OPENMP_BUILD),true)
    $(info [ Doing OpenMP build ])
    $(info )
    APP_CFLAGS   += -fopenmp
    APP_CPPFLAGS += -fopenmp
    APP_LDFLAGS  += -fopenmp
else ifeq ($(OPENCL_BUILD),true)
    $(info [ Doing OpenCL build ])
    $(info )
else
    $(info [ Doing vanilla build (Disabled: OpenMP, OpenCL) ])
    $(info )
endif

# Force enable magickwand build if building magick bin
ifeq ($(BUILD_MAGICK_BIN),true)
    $(info [ Building Magick binary ])
    $(info )
    ifeq ($(BUILD_MAGICKWAND),false)
        $(info [ Force enabling MagickWand build - magick binary requires the MagickWand API ])
        $(info )
        BUILD_MAGICKWAND := true
    endif
endif

# Force enable magickpp build's magickwand
ifeq ($(BUILD_MAGICKPP),true)
    $(info [ Building Magick++ ])
    $(info )
    ifeq ($(BUILD_MAGICKWAND),false)
        $(info [ Force enabling MagickWand build - magick++ requires the MagickWand API ])
        $(info )
        BUILD_MAGICKWAND := true
    endif
endif


