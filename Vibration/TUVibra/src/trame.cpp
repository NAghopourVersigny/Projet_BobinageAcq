#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include "../include/ina219.h"

using namespace std;
int main()
{
  INA219* ina219 = new INA219(0.1, 5);
  
  cout << "Hello word" << endl;
  unsigned char buf[10];
  int file;
  int adapter_nr = 1; /* probably dynamically determined */
  char filename[20];




  snprintf(filename, 19, "/dev/i2c-%d", adapter_nr);
  file = open(filename, O_RDWR);
  if (file < 0)
  {
    cout << "Echec" << endl;
    exit(1);
  }
  int addr = 0x40; /* The I2C address */

  if (ioctl(file, I2C_SLAVE, addr) < 0)
  {
    /* ERROR HANDLING; you can check errno to see what went wrong */
    exit(1);
  }
    buf[0] = 0x04;
  if (write(file, buf, 1) != 1) {
    /* ERROR HANDLING: i2c transaction failed */
  }


  cout << "coucou" << endl;
  /* Using I2C Read, equivalent of i2c_smbus_read_byte(file) */
  if (read(file, buf, 2) != 2)
  {
    cout << "echec" << endl; /* ERROR HANDLING: i2c transaction failed */
  }
  else
  {
    cout << "buf[0] = " << (int)buf[0] << ", buf[1] = " << (int)buf[1] << endl; /* ERROR HANDLING: i2c transaction failed */ /* buf[0] contains the read byte */
  }
  float current();
  cout << current << "mA" << endl;
  close(file);




  return 0;
}