#ifndef IP_FRAG_H
#define IP_FRAG_H

#include <net/ethernet.h>

struct ip_frag_s {
	char *data;
	int datalen;
	pcap_pkthdr header;
	u_char *packet;
	time_t ts;
	char *firstheader;
	u_int32_t firstheaderlen;
	u_int16_t id;
	u_int32_t offset;
	u_int32_t len;
	u_int32_t totallen;
	ip_frag_s *next;
	ip_frag_s *last;
	char has_last;
};

typedef map<unsigned int, ip_frag_s*> ip_frag_queue_t;
typedef map<unsigned int, ip_frag_s*>::iterator ip_frag_queue_it_t;

struct ipfrag_data_s {
	map<unsigned int, map<unsigned int, ip_frag_queue_t*> > ip_frag_stream;
	map<unsigned int, map<unsigned int, ip_frag_queue_t*> >::iterator ip_frag_streamIT;
	map<unsigned int, ip_frag_queue_t*>::iterator ip_frag_streamITinner;
};

void ipfrag_prune(unsigned int tv_sec, int all, ipfrag_data_s *ipfrag_data = NULL);
int handle_defrag(iphdr2 *header_ip, struct pcap_pkthdr **header, u_char **packet, int destroy, ipfrag_data_s *ipfrag_data = NULL);

#endif
