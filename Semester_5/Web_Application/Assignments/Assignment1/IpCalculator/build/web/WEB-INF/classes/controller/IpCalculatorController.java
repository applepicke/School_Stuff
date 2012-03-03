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
/**    Assignment Name/Number/Date :  IP Calculator / 1 / 2/7/2012**/
/**    Optional Comments           :                              **/
/**                                                               **/
/**                                                               **/
/*******************************************************************/
package controller;

import java.util.ArrayList;
import java.util.Collection;
import javax.faces.bean.ManagedBean;
import javax.faces.bean.SessionScoped;
import model.IpCalculatorModel;


/**
 *
 * @author willy
 */
@ManagedBean(name="controller")
@SessionScoped
public class IpCalculatorController {
    
    private IpCalculatorModel ip;
    
    private String baseAddressString;
    private String baseAddressBinary;
    private String maskString;
    private String maskBinary;
    private String broadcastAddressString;
    private String broadcastAddressBinary;    
    private String addressClass;
    private int numberOfHostBits;
    private int numberOfHosts;
    
    private boolean isPrivateAddress;
    private boolean isDefaultRoute;
    private boolean isLoopback;
    private boolean isLinkLocal;
    private boolean isTestNet;
    
    private String subnetMaskString;
    private String subnetMaskBinary;
    private String wildcardMaskString;
    private String wildcardMaskBinary;
    private int subnetBits;
    private int useableSubnets;
    private int hostBitsPerSubnet;
    private int usableHostsPerSubnet;
    
    private String subnetAddressString;
    private String subnetAddressBinary;
    private String firstHostString;
    private String firstHostBinary;
    private String lastHostString;
    private String lastHostBinary;
    private String subnetBroadcastAddressString;
    private String subnetBroadcastAddressBinary;
    
    private Collection prefixValues;

    public IpCalculatorController() {
        super();
        ip = new IpCalculatorModel();
        calculateIpInformation();
        
        //Set up the collection that is used in the drop down menu
        prefixValues = new ArrayList();
        for (int i = 0; i < 31; i++){
            prefixValues.add(i);
        }
    }

    public String getAddressClass() {
        return addressClass;
    }

    public String getBaseAddressBinary() {
        return baseAddressBinary;
    }

    public String getBaseAddressString() {
        return baseAddressString;
    }

    public String getBroadcastAddressBinary() {
        return broadcastAddressBinary;
    }

    public String getBroadcastAddressString() {
        return broadcastAddressString;
    }

    public String getFirstHostBinary() {
        return firstHostBinary;
    }

    public String getFirstHostString() {
        return firstHostString;
    }

    public int getHostBitsPerSubnet() {
        return hostBitsPerSubnet;
    }

    public boolean isIsDefaultRoute() {
        return isDefaultRoute;
    }

    public boolean isIsLinkLocal() {
        return isLinkLocal;
    }

    public boolean isIsLoopback() {
        return isLoopback;
    }

    public boolean isIsPrivateAddress() {
        return isPrivateAddress;
    }

    public boolean isIsTestNet() {
        return isTestNet;
    }

    public IpCalculatorModel getIp() {
        return ip;
    }

    public String getLastHostBinary() {
        return lastHostBinary;
    }

    public String getLastHostString() {
        return lastHostString;
    }

    public String getMaskBinary() {
        return maskBinary;
    }

    public String getMaskString() {
        return maskString;
    }
    
    public int getNumberOfHosts() {
        return numberOfHosts;
    }

    public int getNumberOfHostBits() {
        return numberOfHostBits;
    }

    public Collection getPrefixValues() {
        return prefixValues;
    }

    public String getSubnetAddressBinary() {
        return subnetAddressBinary;
    }

    public String getSubnetAddressString() {
        return subnetAddressString;
    }

    public int getSubnetBits() {
        return subnetBits;
    }

    public String getSubnetMaskBinary() {
        return subnetMaskBinary;
    }

    public String getSubnetMaskString() {
        return subnetMaskString;
    }

    public int getUsableHostsPerSubnet() {
        return usableHostsPerSubnet;
    }

    public int getUseableSubnets() {
        return useableSubnets;
    }

    public String getWildcardMaskBinary() {
        return wildcardMaskBinary;
    }
 
    public String getWildcardMaskString() {
        return wildcardMaskString;
    }


    public String getSubnetBroadcastAddressBinary() {
        return subnetBroadcastAddressBinary;
    }

    public String getSubnetBroadcastAddressString() {
        return subnetBroadcastAddressString;
    }
  
    public final String calculateIpInformation(){
        //Make sure that the ip address is compressed and ready for calculations
        ip.calculate();      
        
        //Perform IP Calculations and assign values to local properties
        baseAddressString = formatIpString(intToIntArray(ip.getBaseAddress()));
        baseAddressBinary = formatIpStringBinary(intToIntArray(ip.getBaseAddress()));
        maskString = formatIpString(intToIntArray(ip.getMaskAddress()));
        maskBinary = formatIpStringBinary(intToIntArray(ip.getMaskAddress()));
        broadcastAddressString = formatIpString(intToIntArray(ip.getBroadcastAddress()));
        broadcastAddressBinary = formatIpStringBinary(intToIntArray(ip.getBroadcastAddress()));
        addressClass = ip.getNetworkClass();
        numberOfHostBits = ip.getNumberOfHostBits();
        numberOfHosts = ip.getNumberOfUsableHosts();
        
        isPrivateAddress = ip.isPrivateAddress();
        isDefaultRoute = ip.isDefaultRoute();
        isLoopback = ip.isLoopback();
        isLinkLocal = ip.isLinkLocal();
        isTestNet = ip.isTestNet();       
        
        subnetMaskString = formatIpString(intToIntArray(ip.getSubnetMask()));
        subnetMaskBinary = formatIpStringBinary(intToIntArray(ip.getSubnetMask()));
        wildcardMaskString = formatIpString(intToIntArray(ip.getWildcardMask()));
        wildcardMaskBinary = formatIpStringBinary(intToIntArray(ip.getWildcardMask()));
        subnetBits = ip.getNumberOfSubnetBits();
        useableSubnets = ip.getNumberOfUsableSubnets();
        hostBitsPerSubnet = ip.getNumberOfHostBitsPerSubnet();
        usableHostsPerSubnet = ip.getNumberOfHostsPerSubnet(); 
        
        subnetAddressString = formatIpString(intToIntArray(ip.getSubnetAddress()));
        subnetAddressBinary = formatIpStringBinary(intToIntArray(ip.getSubnetAddress()));
        firstHostString = formatIpString(intToIntArray(ip.getFirstHost()));
        firstHostBinary = formatIpStringBinary(intToIntArray(ip.getFirstHost()));
        lastHostString = formatIpString(intToIntArray(ip.getLastHost()));
        lastHostBinary = formatIpStringBinary(intToIntArray(ip.getLastHost()));
        subnetBroadcastAddressString = formatIpString(intToIntArray(ip.getSubnetBroadcastAddress()));
        subnetBroadcastAddressBinary = formatIpStringBinary(intToIntArray(ip.getSubnetBroadcastAddress()));
        
        return "index";
    }
    
    
    /**
     * Creates a traditional four octet IP string out of an array of 4 integers
     * representing the four octets of the IP address
     *
     * @param ip An array of 4 IP address octets as integers
     * @return The string formatted IP address
     */
    private String formatIpString(int[] ip) {
        StringBuilder builder = new StringBuilder();
        for (int i = 0; i < 4; i++) {
            builder.append(ip[i]).append('.');
        }
        builder.deleteCharAt(builder.length() - 1);
        return builder.toString();
    }

    /**
     * Creates a string of the binary view of an IP address.
     *
     * @param ip An array of four integers representing an IP Address
     * @return The formatted representation of the binary IP adddress
     */
    private String formatIpStringBinary(int[] ip) {
        StringBuilder builder = new StringBuilder();
        for (int b : ip) {
            for (int i = 128; i > 0; i /= 2) {
                if ((b & i) > 0) {
                    builder.append('1');
                } else {
                    builder.append('0');
                }
            }
            builder.append('.');
        }
        builder.deleteCharAt(builder.length() - 1);
        return builder.toString();
    }
    
     /**
     * Breaks up the four bytes of an integer and returns an array of each octet
     * in integer format. Integers are easier to work with than bytes.
     *
     * @param number The packed integer representing an IP address
     * @return The broken array of integers containing each IP octet
     */
    private int[] intToIntArray(int number) {
        int[] newInt = new int[4];
        for (int i = 3; i >= 0; i--) {
            newInt[i] = (number >>> 8 * (3 - i)) & (0xFF);
        }
        return newInt;
    }
    
    @Override
    public String toString(){
        return "IP Calculator Controller";
    }
    
    
    
}
