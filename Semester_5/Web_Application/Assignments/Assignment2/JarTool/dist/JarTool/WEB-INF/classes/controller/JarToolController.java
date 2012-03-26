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
package controller;

import java.io.Serializable;
import java.util.jar.JarEntry;
import javax.faces.bean.ManagedBean;
import javax.faces.bean.SessionScoped;
import model.JarToolModel;

/**
 *
 * @author willy
 */
@ManagedBean(name = "controller")
@SessionScoped
public class JarToolController implements Serializable {

    private JarToolModel model;

    public JarToolController() {
        model = new JarToolModel();
    }

    /**
     * Get the css style that will determine the styling of the Jar Entry
     * @param entry The jar entry to be styled
     * @return The css class to be used
     */
    public String getEntryCssStyle(JarEntry entry) {
        if (entry.isDirectory()) {
            return "directory";
        } else {
            return "regular_file";
        }
    }

    /**
     * Determine the css style class to use for filters
     * @return The css class to be used
     */
    public String getFilterStyle() {
        if (model.getOptions().isFilters()) {
            return "display: inline";
        } else {
            return "display: none";
        }
    }

    /**
     * Determine whether the jar is runnable
     * @return whether or not the jar can be run
     */
    public boolean getRun() {
        return model.getManifestAttributes().toString().contains("Main-Class");
    }

    public JarToolModel getModel() {
        return model;
    }

    public void setModel(JarToolModel model) {
        this.model = model;
    }

    /**
     * This method is used to test whether or not the new jar name is the same
     * as the current one. If it is, we will send some javascript to take care
     * of client side logic
     *
     * @return
     */
    public boolean testForNameConflict() {
        if (model.getNewJarFileName() == null || model.getNewJarFileName() == null) {
            return false;
        }

        if (model.getNewJarFileName().equals(model.getJarName())) {
            return true;
        }
        return false;
    }

    /**
     * Toggle whether the control column should be displayed or not
     */
    public void toggleControlColumn() {
        boolean current = model.getOptions().isControlColumn();
        model.getOptions().setControlColumn(!current);
    }
}
