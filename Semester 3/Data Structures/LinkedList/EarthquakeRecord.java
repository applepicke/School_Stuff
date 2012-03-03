import java.util.Comparator;

/**
 * This class handles individual earthquake records. <i>Comparator</i> inner classes are defined to provide a sort-ordering mechanism.
 * 
 * @author Rex.Woollard@AlgonquinCollege.com
 * @author Updated by: coll0300@algonquinlive.com
 */
public class EarthquakeRecord {
	private int nYear;
	private int nMonth;
	private int nDay;
	private int nHour;
	private int nMinute;
	private double dSecond;
	private int nUTC;
	private double dLatitude;
	private double dLongitude;
	private double dMagnitude;
	private int nDepth;
	private int nEpicentre;
	private double dCityLatitude;
	private double dCityLongitude;
	private String sCityName;

	public EarthquakeRecord(String sRawRecord) { parseStringInput(sRawRecord); }

	/**
	 * Accepts a <i>String</i> of data and parses into component data-typed fields.
	 * 
	 * @param sRawRecord <i>String</i> of data from input source
	 */
	private void parseStringInput(String sRawRecord) {
		try {
			nYear = Integer.parseInt(sRawRecord.substring(0, 4));
		} catch (java.lang.NumberFormatException e) {
			nYear = 0;
		}
		try {
			nMonth = Integer.parseInt((sRawRecord.substring(5, 7)).trim());
		} catch (java.lang.NumberFormatException e) {
			nMonth = 0;
		}
		try {
			nDay = Integer.parseInt((sRawRecord.substring(8, 10)).trim());
		} catch (java.lang.NumberFormatException e) {
			nDay = 0;
		}
		try {
			nHour = Integer.parseInt((sRawRecord.substring(11, 13)).trim());
		} catch (java.lang.NumberFormatException e) {
			nHour = 0;
		}
		try {
			nMinute = Integer.parseInt((sRawRecord.substring(14, 16)).trim());
		} catch (java.lang.NumberFormatException e) {
			nMinute = 0;
		}
		try {
			dSecond = Double.parseDouble((sRawRecord.substring(17, 21)).trim());
		} catch (java.lang.NumberFormatException e) {
			dSecond = 0.0;
		}
		try {
			nUTC = Integer.parseInt((sRawRecord.substring(23, 25)).trim());
		} catch (java.lang.NumberFormatException e) {
			nUTC = 0;
		}
		try {
			dLatitude = Double.parseDouble((sRawRecord.substring(30, 37)).trim());
		} catch (java.lang.NumberFormatException e) {
			dLatitude = 0.0;
		}
		try {
			dLongitude = Double.parseDouble((sRawRecord.substring(38, 46)).trim());
		} catch (java.lang.NumberFormatException e) {
			dLongitude = 0.0;
		}
		try {
			dMagnitude = Double.parseDouble((sRawRecord.substring(46, 49)).trim());
		} catch (java.lang.NumberFormatException e) {
			dMagnitude = 0.0;
		}
		try {
			nDepth = Integer.parseInt((sRawRecord.substring(50, 54)).trim());
		} catch (java.lang.NumberFormatException e) {
			nDepth = 0;
		}
		try {
			nEpicentre = Integer.parseInt((sRawRecord.substring(56, 61)).trim());
		} catch (java.lang.NumberFormatException e) {
			nEpicentre = 0;
		}
		try {
			dCityLatitude = Double.parseDouble((sRawRecord.substring(62, 71)).trim());
		} catch (java.lang.NumberFormatException e) {
			dCityLatitude = 0.0;
		}
		try {
			dCityLongitude = Double.parseDouble((sRawRecord.substring(72, 81)).trim());
		} catch (java.lang.NumberFormatException e) {
			dCityLongitude = 0.0;
		}
		sCityName = sRawRecord.substring(93, 124).trim();
	}
	public int getYear() { return nYear; }
	public int getMonth() { return nMonth; }
	public int getDay() { return nDay; }
	public int getHour() { return nHour; }
	public int getMinute() { return nMinute; }
	public double getSecond() { return dSecond; }
	public int getUTC() { return nUTC; }
	public double getLatitude() { return dLatitude; }
	public double getLongitude() { return dLongitude; }
	public double getMagnitude() { return dMagnitude; }
	public int getDepth() { return nDepth; }
	public int getEpicentre() { return nEpicentre; }
	public double getCityLatitude() { return dCityLatitude; }
	public double getCityLongitude() { return dCityLongitude; }
	public String getCityName() { return sCityName; }

	public String toString() {
		return String.format("%4d/%2d/%2d %2d:%2d:%2.1f %d Lat/Long:%6.2f,%6.2f Mag:%3.1f Depth:%4d %5d %6.2f:%6.2f %s", nYear, nMonth, nDay, nHour, nMinute, dSecond, nUTC, dLatitude, dLongitude,
		    dMagnitude, nDepth, nEpicentre, dCityLatitude, dCityLongitude, sCityName);
	}

	// Singleton private inner class that creates a <i>Comparator</i> object if needed; used to compare <i>EarthquakeRecord</i> objects based on <i>String</i> containing City Name 
	public static class CompareCityName implements Comparator<EarthquakeRecord>{
		final public static CompareCityName instance = new CompareCityName();
		private CompareCityName(){}
		//@Override
		public int compare(EarthquakeRecord record1, EarthquakeRecord record2){
			return (record1.sCityName.compareTo(record2.sCityName));
		}
	}

	// Singleton private inner class that creates a <i>Comparator</i> object if needed; used to compare <i>EarthquakeRecord</i> objects based on <i>dMagnitude</i> 
	public static class CompareMagnitude implements Comparator<EarthquakeRecord>{
		final public static CompareMagnitude instance = new CompareMagnitude();
		private CompareMagnitude(){}
		//@Override
		public int compare(EarthquakeRecord record1, EarthquakeRecord record2){
			if (record1.dMagnitude > record2.dMagnitude)
				return 1;
			else if (record1.dMagnitude < record2.dMagnitude)
				return -1;
			else return 0;
			
		}
	}

	// Singleton private inner class that creates a <i>Comparator</i> object if needed; used to compare <i>EarthquakeRecord</i> objects based on <i>nDepth</i> 
	public static class CompareDepth implements Comparator<EarthquakeRecord>{
		final public static CompareDepth instance = new CompareDepth();
		private CompareDepth(){}
		//@Override
		public int compare(EarthquakeRecord record1, EarthquakeRecord record2){
			return (record1.nDepth - record2.nDepth);
		}
	}
	
	// implement <i>Comparator</i> class to compare two EarthquakeRecord objects based on nDepth

}