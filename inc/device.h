#ifndef DEVICE
#define DEVICE

void   device_setup(void);
device initializeDevice(int,char *,int,void*,int);
device *getDevice(int,int);
device *getDeviceByIRQ(int);

#endif
