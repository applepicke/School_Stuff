/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package org.netbeans.saas.google;

import java.io.IOException;
import org.netbeans.saas.RestConnection;
import org.netbeans.saas.RestResponse;

/**
 * GoogleGeocodingService Service
 *
 * @author willy
 */
public class GoogleGeocodingService {

    /**
     * Creates a new instance of GoogleGeocodingService
     */
    public GoogleGeocodingService() {
    }
    
    private static void sleep(long millis) {
        try {
            Thread.sleep(millis);
        } catch (Throwable th) {
        }
    }

    /**
     *
     * @param q
     * @param output
     * @return an instance of RestResponse
     */
    public static RestResponse geocode(String q, String output) throws IOException {
        String apiKey = GoogleGeocodingServiceAuthenticator.getApiKey();
        String[][] pathParams = new String[][]{};
        String[][] queryParams = new String[][]{{"q", q}, {"key", "" + apiKey + ""}, {"output", output}};
        RestConnection conn = new RestConnection("http://maps.google.com/maps/geo", pathParams, queryParams);
        sleep(1000);
        return conn.get(null);
    }
}
