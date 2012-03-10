/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package model;

import java.io.Serializable;
import org.netbeans.saas.RestResponse;
import org.netbeans.saas.google.GoogleGeocodingService;

/**
 *
 * @author William Collins (coll0300@algonquinlive.com)
 */
public class GeocodeClient implements Serializable{
    
    
    public static String convertAddressToLatitudeAndLongitude( String address ) {

       
        try {
                 String q = address;
                 String output = "csv";

             RestResponse result = GoogleGeocodingService.geocode(q, output);
             String[] resultAsArray = result.getDataAsString().split(",");
             return resultAsArray[2] + ", " + resultAsArray[3];
             //TODO - Uncomment the print Statement below to print result.
             //System.out.println("The SaasService returned: "+result.getDataAsString());
        } catch (Exception ex) {
             ex.printStackTrace();
        }
        //could not map address
        return "0.0, 0.0";

        
        
    }

}
