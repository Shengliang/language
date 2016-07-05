
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <linux/if.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>


int main(int argc, char* argv[])
{
  struct ifreq ifr;
  char* n = "eth0";
  int fd = socket(PF_INET, SOCK_DGRAM, IPPROTO_IP);

  if (argc >= 2)
	n = argv[1];
  memset(&ifr, 0x0, sizeof(ifr));
  strncpy(ifr.ifr_name, n, IFNAMSIZ-1);

  if (0 == ioctl(fd, SIOCGIFHWADDR, &ifr)) {
    int i;
    printf("MAC:");
    for (i = 0; i < 6; ++i)
      printf("%02X%s", (unsigned char) ifr.ifr_addr.sa_data[i], i==5? "": " ");
    printf("\n");
  }

  if (0 == ioctl(fd, SIOCGIFADDR, &ifr)) {
    printf("IP:%s\n", inet_ntoa( ((struct sockaddr_in *) &ifr.ifr_addr)->sin_addr));
  }
  if (0 == ioctl(fd, SIOCGIFNETMASK, &ifr)) {
    printf("MASK:%s\n", inet_ntoa( ((struct sockaddr_in *) &ifr.ifr_addr)->sin_addr));
  }
  if (0 == ioctl(fd, SIOCGIFMTU, &ifr)) {
    printf("MTU:%d\n", ifr.ifr_mtu);
  }

  close(fd);
  return 0;
}
