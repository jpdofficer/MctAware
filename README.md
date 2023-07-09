# MctAware
A way to track computers in vehicles by using arp
The purpose of this program is to meet CJIS requirements. It is required to be able to account for all computers in vehicles when used in a public service manner. In our organization we call computers that are mobile MCT, which stands for Mobile Computer Terminals. In order to meet with CJIS requirements we needed a way to account for all MCTs. It does this by association mac address for mac address. To meet the requirements of this application it needed to do the following
1. Be completely independant of the network hardware. While we cannot escape the OSI model we can use the tools provided in order to determine the interfaces and if the can see the next hop.
2. I wanted this application to be completely independant of the hardware and while C# was great for windows the gui aspect tended to be lacking
3. I decided to use the qt library in order to complete this take in order to do this as open source as possible, other than what may be confidential to public service operations.
