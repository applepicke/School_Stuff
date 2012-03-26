/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package model;

import java.io.Serializable;
import java.util.zip.ZipEntry;


/**
 *
 * @author willy
 */
public class JarEntry extends java.util.jar.JarEntry implements Serializable {

    public JarEntry(String name){
        super(name);
    }
    
    public JarEntry(java.util.jar.JarEntry entry){
        super(entry);
    }
    
    public JarEntry(ZipEntry entry){
        super(entry);
    }
 
}
