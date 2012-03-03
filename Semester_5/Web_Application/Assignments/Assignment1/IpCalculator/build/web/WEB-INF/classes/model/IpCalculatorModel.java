/*******************************************************************/
/**                                                               **/
/**                                                               **/
/**    Student Name                :  William Collins             **/
/**    EMail Address               :  coll0300@algonquinlive.com  **/
/**    Student Number              :  040652633                   **/
/**    Student User ID             :  coll0300                    **/
/**    Course Number               :  CST 8218                    **/
/**    Lab Section Number          :  310                         **/
/**    Professor Name              :  Gerald Hurdle               **/
/**    Assignment Name/Number/Date :  IP Calculator / 1 / 2/9/2012**/
/**    Optional Comments           :                              **/
/**                                                               **/
/**                                                               **/
/*******************************************************************/
package model;

import java.io.Serializable;

/**
 *
 * @author willy
 */
public class IpCalculatorModel implements Serializable {

    /*
     * CLASS VALUES
     */
    private static final int CLASS_A_MASK = 0x80000000;
    private static final int CLASS_B_MASK = 0xC0000000;
    private static final int CLASS_C_MASK = 0xC0000000;
    private static final int CLASS_A = 0x00000000;
    private static final int CLASS_B = 0x80000000;
    private static final int CLASS_C = 0xC0000000;
    
    /*
     * MASKS - masks used for determining certain characteristics of an adress
     */
    private static final int DEFAULT_ROUTE_MASK = 0xFF000000;
    private static final int LOOPBACK_MASK = 0xFF000000;
    private static final int LINK_LOCAL_MASK = 0xFFFF0000;
    private static final int TEST_NET_MASK = 0xFFFFFF00;
    private static final int[] PRIVATE_ADDRESS_MASKS = {
        0xFF000000,
        0xFFF00000,
        0xFFFF0000
    };
    /*
     * ADDRESS BLOCKS - The IP blocks of certain known address types
     */
    private static final int DEFAULT_ROUTE = 0x00000000;
    private static final int LOOPBACK = 0x7F000000;
    private static final int LINK_LOCAL = 0xA9FE0000;
    private static final int TEST_NET = 0xC0000200;
    private static final int[] PRIVATE_ADDRESSES = {
        0x0A000000, //10.0.0.0 - 10.255.255.255 
        0xAC100000, //172.16.0.0 - 172.31.255.255
        0xC0A80000 //192.168.0.0 - 192.168.255.255   
    };
    
    //The octets are bean properties represting the octets in an IP address
    private int octet1;
    private int octet2;
    private int octet3;
    private int octet4;
    
    private int address; //The IP address
    private int mask;    //The mask representation of the network prefix
    private int broadcast; //The broadcast address of the subnet
    private int network; //The network address of the subnet
    private int classNetworkMask; //Mask of the class type of the network.

    public IpCalculatorModel() {
        //A nice set of default values for the octet and prefix fields
        octet1 = 192;
        octet2 = 168;
        octet3 = 0;
        octet4 = 1;
        mask = 0xFFFFFF00;
    }

    /**
     * Retrieves the subnet prefix from the local bit mask for the address
     *
     * @return An integer value representing a subnet prefix
     */
    public int getMask() {
        int tally = 0;
        //tally the number of bits from the left hand side of the mask
        for (int i = 0; i < 32; i++) {
            tally += ((mask << i) & 0xEFFFFFFF) >>> 31;
        }
        return tally;
    }

    /**
     * Takes an integer representing a prefix, and converts it to a compress
     * integer bitmask.
     *
     * @param prefix The subnet prefix representing the bit mask
     */
    public void setMask(int prefix) {
        int localmask = 0;
        for (int i = 0; i < prefix; i++) {
            localmask |= (0x80000000 >>> i);
        }
        this.mask = localmask;
    }

    public int getOctet1() {
        return octet1;
    }

    public void setOctet1(int octet1) {
        this.octet1 = octet1;
    }

    public int getOctet2() {
        return octet2;
    }

    public void setOctet2(int octet2) {
        this.octet2 = octet2;
    }

    public int getOctet3() {
        return octet3;
    }

    public void setOctet3(int octet3) {
        this.octet3 = octet3;
    }

    public int getOctet4() {
        return octet4;
    }

    public void setOctet4(int octet4) {
        this.octet4 = octet4;
    }

    /**
     * *********CALCULATION METHODS***************
     */
    public int getBaseAddress() {
        return (address & classNetworkMask);
    }
    
    public int getSubnetAddress() {
        return network;

    }

    public int getMaskAddress() {
        return classNetworkMask;
    }
    
    public int getSubnetMask(){
        return mask;
    }

    public int getBroadcastAddress(){
        return address | (~classNetworkMask);
    }
    
    public int getSubnetBroadcastAddress() {
        return broadcast;
    }

    public String getNetworkClass() {
        if ( (address & CLASS_A_MASK) == CLASS_A) {
            return "A";
        }
        if ( (address & CLASS_B_MASK) == CLASS_B) {
            return "B";
        }
        if ( (address & CLASS_C_MASK) == CLASS_C) {
            return "C";
        }
        return "Unknown";
    }

    public int getNumberOfHostBitsPerSubnet() {
        return calculateNumberOfHostBits(mask);
    }

    public int getNumberOfHostBits() {
        return calculateNumberOfHostBits(classNetworkMask);       
    }

    public int getNumberOfUsableHosts() {
        return (int) Math.pow(2.0, (double) getNumberOfHostBits()) - 2;
    }

    public int getNumberOfHostsPerSubnet() {
        return (int) Math.pow(2.0, (double) getNumberOfHostBitsPerSubnet()) - 2;
    }

    public int getNumberOfSubnetBits() {
        int subnetBits = getNumberOfHostBits() - getNumberOfHostBitsPerSubnet();
        if (subnetBits < 0)
            subnetBits = 0;
        return subnetBits;
    }

    public int getNumberOfUsableSubnets() {
        int subnetBits = getNumberOfSubnetBits();
        if (subnetBits == 0)
            return 0;
        return (int) Math.pow(2, getNumberOfSubnetBits());
    }

    public int getWildcardMask() {
        return ~mask;
    }

    public int getFirstHost() {
        return network + 1;
    }

    public int getLastHost() {
        return broadcast - 1;
    }

    public boolean isPrivateAddress() {
        for (int i = 0; i < 3; i++) {
            if ((address & PRIVATE_ADDRESS_MASKS[i]) == PRIVATE_ADDRESSES[i])
                return true;          
        }
        return false;
    }

    public boolean isDefaultRoute() {
        if ((address & DEFAULT_ROUTE_MASK) == DEFAULT_ROUTE)
            return true;
        return false;
    }

    public boolean isLoopback() {
        if ((address & LOOPBACK_MASK) == LOOPBACK) 
            return true;
        return false;
    }

    public boolean isLinkLocal() {
        if ((address & LINK_LOCAL_MASK) == LINK_LOCAL) 
            return true;
        return false;
    }

    public boolean isTestNet() {
        if ((address & TEST_NET_MASK) == TEST_NET) 
            return true;
        return false;
    }

    /**
     * This method should only be invoked after reading in all four IP octets.
     * It will pack the octets into a single integer variable in order to 
     * ease the process of manipulating and analyzing the bits inside.
     */
    public void calculate() {
        compressOctetsToInt();
        calculateSubnetBroadcastAddress();
        calculateNetworkAddress();
        calculateAddressClass();
    }

    private void calculateSubnetBroadcastAddress() {
        broadcast = (~mask) | address;
    }

    private void calculateNetworkAddress() {
        network = address & mask;
    }
    
    private void calculateAddressClass() {
        if ((address & CLASS_A_MASK) == CLASS_A) {
            classNetworkMask = 0xFF000000;
        }
        else if ((address & CLASS_B_MASK) == CLASS_B) {
            classNetworkMask = 0xFFFF0000;
        }
        else if ((address & CLASS_C_MASK) == CLASS_C) {
            classNetworkMask = 0xFFFFFF00;
        }
        else 
            classNetworkMask = 0x00000000;
    }

    
    /**
     * Calculates the number of host bits given a network or subnet mask.
     * @param mask The network or subnet mask to be analyzed
     * @return The number of host bits in the mask
     */
    private int calculateNumberOfHostBits(int mask){
        int tally = 0;
        while ((~mask >>> tally) != 0) {
            tally++;
            if (tally > 32) return 32;
        }
        return tally;
    }

    /**
     * Takes the octet properties that are mapped to the jsf page and packs them
     * into a single integer names "address". This allows for easy bitwise
     * operations using the mask.
     */
    private void compressOctetsToInt() {
        address = 0;
        address |= octet1 << 24;
        address |= octet2 << 16;
        address |= octet3 << 8;
        address |= octet4;
    }

    @Override
    public String toString() {
        return "IP Calculator Model";
    }
    
}
