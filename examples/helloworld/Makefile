TARGET_NAME := helloworld

include Makefile.libretro

ifeq ($(STATIC_LINKING),1)
	FLAGS += -DSTATIC_LINKING
endif

FLAGS += -D__LIBRETRO__ $(COREDEFINES) $(ENDIANNESS_DEFINES) $(PLATFORM_DEFINES) $(WARNINGS) $(fpic)

CXXFLAGS += $(FLAGS) -std=c++14
CFLAGS += $(FLAGS) -std=gnu99

# Ignore first attempt builds, and re-try for a cleaner dependency chain.
all: $(TARGET)
	$(MAKE) $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) -c -o $@ $< $(CXXFLAGS)

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

%.o: %.m
	$(CC) -c -o $@ $< $(CFLAGS)

%.o: %.S
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -f $(TARGET) $(OBJECTS)

test: unittest
	@echo "Run the testing suite by using:\n\n    retroarch -L $(TARGET) myfile.txt\n\n"
