OBJDIR=objs

CFLAGS=-g -O3 -I/usr/local/include/opencv -I/usr/local/include/opencv2 -MD
LDFLAGS=-lopencv_highgui -lopencv_core -lopencv_video -lopencv_features2d -lopencv_calib3d -lopencv_imgproc -lpthread -lm -lopencv_videoio -lopencv_objdetect  -lX11 -lXext -lrt -lstdc++ -L../raspberrypi/userland/build/lib -lmmal_core -lmmal -l mmal_util -lvcos -lbcm_host -L. libraspicamcv.a 

OBJS = \
	$(OBJDIR)/RaspiCamMain.o \
	$(OBJDIR)/MyOpenCVIF.o \
	$(OBJDIR)/HumanDetector.o \
	$(OBJDIR)/HUD.o \
	$(OBJDIR)/FPSCounter.o \
	$(OBJDIR)/SystemMonitor.o 

VPATH = MyOpenCV

TARGETS = raspicam_cvlan

all: $(TARGETS)

$(OBJDIR)/%.o: %.cpp
	g++ -c $(CFLAGS) $< -o $@

raspicam_cvlan: $(OBJS)
	make -C ../robidouille/raspicam_cv/
	cp ../robidouille/raspicam_cv/libraspicamcv.* .
	g++ $+ $(LDFLAGS) $(LDFLAGS2) -o $@

cleanall: clean cleanlib

clean:
	rm -f $(OBJDIR)/* $(TARGETS)

cleanlib:
	rm -f libraspicamcv.*
	make -C ../robidouille/raspicam_cv/ clean

-include $(OBJDIR)/*.d
