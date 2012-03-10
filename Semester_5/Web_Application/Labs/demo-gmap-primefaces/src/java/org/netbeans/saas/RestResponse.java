/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package org.netbeans.saas;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.io.StringReader;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.xml.bind.JAXBContext;
import javax.xml.bind.JAXBElement;
import javax.xml.bind.JAXBException;
import javax.xml.bind.Unmarshaller;
import javax.xml.transform.stream.StreamSource;

/**
 * RestResponse
 *
 * @author willy
 */
public class RestResponse {

    private ByteArrayOutputStream os;
    private String contentType = "text/plain";
    private String contentEncoding;
    private int responseCode;
    private String responseMsg;
    private long lastModified;
    
    public RestResponse() {
        os = new ByteArrayOutputStream();
    }
    
    public RestResponse(byte[] bytes) throws IOException {
        this();
        
        byte[] buffer = new byte[1024];
        int count = 0;
        ByteArrayInputStream bis = new ByteArrayInputStream(bytes);
        while ((count = bis.read(buffer)) != -1) {
            write(buffer, 0, count);
        }
    }
    
    public void setContentType(String contentType) {
        this.contentType = contentType;
    }
    
    public String getContentType() {
        return contentType;
    }
    
    public void setContentEncoding(String contentEncoding) {
        this.contentEncoding = contentEncoding;
    }
    
    public void setResponseMessage(String msg) {
        this.responseMsg = msg;
    }
    
    public String getResponseMessage() {
        return responseMsg;
    }
    
    public void setResponseCode(int code) {
        this.responseCode = code;
    }
    
    public int getResponseCode() {
        return responseCode;
    }
    
    public void setLastModified(long lastModified) {
        this.lastModified = lastModified;
    }
    
    public long getLastModified() {
        return lastModified;
    }
    
    public void write(byte[] bytes, int start, int length) {
        os.write(bytes, start, length);
    }
    
    public byte[] getDataAsByteArray() {
        return os.toByteArray();
    }
    
    public String getDataAsString() {
        try {
            return os.toString("UTF-8");
        } catch (Exception ex) {
            Logger.getLogger(RestConnection.class.getName()).log(Level.SEVERE, null, ex);
        }
        
        return null;
    }
    
    public OutputStream getOutputStream() {
        return os;
    }
    
    public <T> T getDataAsObject(Class<T> jaxbClass) throws JAXBException {
        return getDataAsObject(jaxbClass, jaxbClass.getPackage().getName());
    }
    
    public <T> T getDataAsObject(Class<T> clazz, String packageName) throws JAXBException {
        JAXBContext jc = JAXBContext.newInstance(packageName);
        Unmarshaller u = jc.createUnmarshaller();
        Object obj = u.unmarshal(new StreamSource(new StringReader(getDataAsString())));
        
        if (obj instanceof JAXBElement) {
            return (T) ((JAXBElement) obj).getValue();
        } else {
            return (T) obj;
        }        
    }
}
