/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package bean;

import java.io.Serializable;
import javax.faces.bean.ManagedBean;
import javax.faces.bean.SessionScoped;
import model.GeocodeClient;

/**
 *
 * @author William Collins (coll0300@algonquinlive.com)
 */
@ManagedBean(name = "bean")
@SessionScoped
public class UnnormalizedAddress implements Serializable {

    public static String ALGONQUIN_COLLEGE;
    
    static {
        ALGONQUIN_COLLEGE = "1385 Woodroffe Ave., Ottawa, ON, Canada, K2G 1V8";
    }
    private String address;

    public UnnormalizedAddress() {
        super();

        this.address = ALGONQUIN_COLLEGE;
    }

    public String getLatitudeAndLongitude() {
        return GeocodeClient.convertAddressToLatitudeAndLongitude( address );

    }

    public String getAddress() {
        return address;
    }

    public void setAddress(String address) {
        this.address = address;
    }
}
