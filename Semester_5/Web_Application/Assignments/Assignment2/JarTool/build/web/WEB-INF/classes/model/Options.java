/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package model;

import java.io.Serializable;

/**
 *
 * @author willy
 */
public class Options implements Serializable{
    
    private boolean controlColumn;
    private boolean detailColumns;
    private boolean filters;
    
    private boolean compression;

    public Options(){
        controlColumn = true;
        detailColumns = false;
        filters = false;
        compression = false;
    }
    
    public boolean isControlColumn() {
        return controlColumn;
    }

    public void setControlColumn(boolean controlColumn) {
        this.controlColumn = controlColumn;
    }

    public boolean isDetailColumns() {
        return detailColumns;
    }

    public void setDetailColumns(boolean detailColumns) {
        this.detailColumns = detailColumns;
    }

    public boolean isFilters() {
        return filters;
    }

    public void setFilters(boolean filters) {
        this.filters = filters;
    }

    public boolean isCompression() {
        return compression;
    }

    public void setCompression(boolean compression) {
        this.compression = compression;
    }
    

    
}
