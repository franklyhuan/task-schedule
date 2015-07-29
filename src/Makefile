# This Makefile requires GNU make.

HOME = ..

include $(HOME)/Defines.mk


ifeq ($(LINKAGE),dynamic)
CFLAGS += -fPIC -O3
endif

.PHONY: default all clean

SRCS := \
	task_queue.cpp \
        thread_pool.cpp
#
OBJS := ${SRCS:.cpp=.o}

default: all

all: $(HOME)/$(LIB_DIR)/$(TARGET)

$(HOME)/$(LIB_DIR)/$(TARGET): $(TARGET)
	cp $< $(HOME)/$(LIB_DIR)

$(LIB_PHOENIX).a: $(OBJS)
	$(AR) cr $@ $(OBJS)
	$(RANLIB) $@

$(LIB_PHOENIX).so: $(OBJS)
	$(CXX) --shared -o $@ $(OBJS)

%.o: %.cpp
	$(CXX) $(CFLAGS) -c $< -o $@ -I$(HOME)/$(INC_DIR)
 
clean:
	rm -f $(HOME)/$(LIB_DIR)/$(TARGET) $(TARGET) $(OBJS)
