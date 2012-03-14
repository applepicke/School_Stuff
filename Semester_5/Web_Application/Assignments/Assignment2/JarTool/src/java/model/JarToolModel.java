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
/**    Assignment Name/Number/Date :  JarTool / 2 / 3/9/2012**/
/**    Optional Comments           :                              **/
/**                                                               **/
/**                                                               **/
/*******************************************************************/
package model;

import java.io.*;
import java.text.AttributedCharacterIterator.Attribute;
import java.util.ArrayList;
import java.util.Enumeration;
import java.util.List;
import java.util.Map.Entry;
import java.util.jar.JarFile;
import java.util.jar.JarOutputStream;
import java.util.zip.CRC32;
import java.util.zip.ZipEntry;
import java.util.zip.ZipException;
import javax.faces.context.FacesContext;
import org.apache.commons.io.FileUtils;
import org.apache.commons.io.IOUtils;
import org.primefaces.component.commandbutton.CommandButton;
import org.primefaces.component.datatable.DataTable;
import org.primefaces.event.FileUploadEvent;
import org.primefaces.model.DefaultStreamedContent;
import org.primefaces.model.StreamedContent;
import org.primefaces.util.ComponentUtils;

/**
 *
 * @author willy
 */
public class JarToolModel implements Serializable {

    private transient ArrayList<JarEntry> jarEntries;
    private transient ArrayList<Entry<String, Attribute>> manifestAttributes;
    private Options options;
    
    private String jarName;
    private String newJarFileName;
    
    /**
     * The Jar Entry to be displayed in detail
     */
    private transient JarEntry detailEntry;


    public JarToolModel() {
        options = new Options();
        jarEntries = new ArrayList<JarEntry>();
        manifestAttributes = new ArrayList<Entry<String, Attribute>>();
    }

    public Options getOptions() {
        return options;
    }

    public void setOptions(Options options) {
        this.options = options;
    }

    public List<JarEntry> getJarEntries() {
        return jarEntries;
    }

    public void setJarEntries(ArrayList<JarEntry> jarEntries) {
        this.jarEntries = jarEntries;
    }

    public ArrayList<Entry<String, Attribute>> getManifestAttributes() {
        return manifestAttributes;
    }

    public void setManifestAttributes(ArrayList<Entry<String, Attribute>> manifestEntries) {
        this.manifestAttributes = manifestEntries;
    }

    public JarEntry getDetailEntry() {
        return detailEntry;
    }

    public void setDetailEntry(JarEntry detailEntry) {
        this.detailEntry = detailEntry;
    }

    public String getNewJarFileName() {
        return newJarFileName;
    }

    public String getJarName() {
        return jarName;
    }

    public void setJarName(String jarName) {
        this.jarName = jarName;
    }

    
    
    
    public void setNewJarFileName(String newJarFileName) {
        if (!newJarFileName.endsWith(".jar")){
            newJarFileName = newJarFileName + ".jar";
        }      
        this.newJarFileName = newJarFileName;
    }
       
    public void loadJar(FileUploadEvent event) throws IOException {
        File fileToWrite = new File(event.getFile().getFileName());
        FileOutputStream oStream; //Stream to write the file to

        //Check to see if the file exists first. If it doesn't, create it.
        if (fileToWrite.exists()) {
            fileToWrite.delete();
        }
        fileToWrite.createNewFile();

        oStream = new FileOutputStream(fileToWrite);
        oStream.write(event.getFile().getContents());
        oStream.close();

        //Initialize member variables to jar file values
        JarFile jar;
        try {
            jar = new JarFile(fileToWrite);
        }
        catch (ZipException e){
            //gracefully exit
            return;
        }
        
        Enumeration<java.util.jar.JarEntry> entries = jar.entries();
        jarEntries = new ArrayList<JarEntry>();
        //Get the entries in the jar file
        while (entries.hasMoreElements()) {
            JarEntry entry = new JarEntry(entries.nextElement());
            jarEntries.add(entry);
        }
        manifestAttributes = new ArrayList(jar.getManifest().getMainAttributes().entrySet());
        jarName = jar.getName();
       
        jar.close();
        
        resetTable();

    }

    public StreamedContent saveFileFromJar(String name) throws IOException {
        String nameMinusPath = name.substring(name.lastIndexOf('/') + 1, name.length());
        
        JarFile jar = new JarFile(jarName);        
        InputStream stream = jar.getInputStream(jar.getJarEntry(name));
        StreamedContent content = new DefaultStreamedContent(stream, null, nameMinusPath);
        return content;
    }
    
    public StreamedContent downloadJar() throws IOException{
        JarFile jar = new JarFile(jarName);
        FileOutputStream oStream = new FileOutputStream("temp.jar");
        JarOutputStream jos = new JarOutputStream(oStream);
        
        writeEntriesToJarFile(jar, jos);               
        FileInputStream iStream = new FileInputStream("temp.jar");
        StreamedContent jarToDownload = new DefaultStreamedContent(iStream, null, jar.getName());
        
        jos.close();
        jar.close();
        
        resetTable();
        
        return jarToDownload;
    }
    
    private void writeEntriesToJarFile(JarFile jar, JarOutputStream jos) throws IOException{
        for (ZipEntry entry: jarEntries){
            jos.putNextEntry(entry);
            jos.write(IOUtils.toByteArray(jar.getInputStream(entry)));
            jos.closeEntry();
        }
    }

    public void addFileToJar(FileUploadEvent event) throws IOException { 
        String fileName = event.getFile().getFileName();
        JarFile jar = new JarFile(jarName);
        JarEntry entry = new JarEntry(fileName);
        FileOutputStream fos = new FileOutputStream("temp.jar");
        JarOutputStream jos = new JarOutputStream(fos);
        
        //Add appropriate compression
        if (options.isCompression()) {
            entry.setMethod(JarEntry.DEFLATED);
        } else {
            //Uncompressed means certain fields need to be set
            entry.setMethod(JarEntry.STORED);
            entry.setSize(event.getFile().getSize());
            entry.setCompressedSize(event.getFile().getSize());
            CRC32 crc = new CRC32();
            crc.update(event.getFile().getContents());
            entry.setCrc(crc.getValue());
        }        
        //Write all current entries in the list to the jar file
        try {
            writeEntriesToJarFile(jar, jos);
            jar.close();
            
                    //Write the new entry to the jar file
        jos.putNextEntry(entry);
        jos.write(event.getFile().getContents());
        jos.close();
        
        //Add entry to list of entries
        jar = new JarFile("temp.jar");  
        JarEntry zip = new JarEntry(jar.getJarEntry(entry.getName()));
        jarEntries.add(zip);
        
        //Overwrite the original jar with the new one
        File temp = new File("temp.jar");
        File jarFile = new File(jarName);
        FileUtils.copyFile(temp, jarFile);
        }
        catch (ZipException e){
            System.out.println("Duplicate file tried to be added. Disregarding.");
        }
        
        //Clean up
        jar.close(); 
        
        resetTable();
    }

    public void runJar() throws IOException {
        JarFile jar = new JarFile(jarName);
        Runtime.getRuntime().exec("java -jar " + jar.getName());
        jar.close();
    }
    
    public void createJar() throws IOException{
           
        if (newJarFileName.equals(jarName)){
            FacesContext facesContext = FacesContext.getCurrentInstance();
            CommandButton button = (CommandButton) ComponentUtils.findComponent(facesContext.getViewRoot(), "newJarButton");
            button.setOnerror(jarName);
        }
        
        //Create the file locally
        FileOutputStream fos = new FileOutputStream(newJarFileName);
        JarOutputStream jos = new JarOutputStream(fos);
        
        JarEntry manifest = new JarEntry("MANIFEST/MANIFEST.MF");
        jos.putNextEntry(manifest);        
        jos.close();
        
        jarName = newJarFileName;   
        
        jarEntries = new ArrayList<JarEntry>();
        manifestAttributes = new ArrayList<Entry<String, Attribute>>();
        
        
        resetTable();
    }
    
    /**
     * resets the jar entries table. This is to prevent an update bug caused by the
     * primefaces dataTable filtering.
     */
    private void resetTable(){
        FacesContext facesContext = FacesContext.getCurrentInstance();
        DataTable table = (DataTable) ComponentUtils.findComponent(facesContext.getViewRoot(), "jarEntries");
        table.resetValue();

    }
    
}
