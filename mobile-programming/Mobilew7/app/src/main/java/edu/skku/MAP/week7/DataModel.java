package edu.skku.MAP.week7;

public class DataModel {
    private String Title;
    private String Year;
    private String Released;
    private String Runtime;
    private String Genre;
    private String imdbRating;
    private String Metascore;

    public String getGenre() {
        return Genre;
    }

    public String getIMDB_Rates() {
        return imdbRating;
    }

    public String getMetascore() {
        return Metascore;
    }

    public String getReleased_Date() {
        return Released;
    }

    public String getRuntime() {
        return Runtime;
    }

    public String getTitle() {
        return Title;
    }

    public String getYear() {
        return Year;
    }

    public void setGenre(String genre) {
        Genre = genre;
    }

    public void setIMDB_Rates(String IMDB_Rates) {
        this.imdbRating = IMDB_Rates;
    }

    public void setMetascore(String metascore) {
        Metascore = metascore;
    }

    public void setReleased_Date(String Released) {
        Released = Released;
    }

    public void setRuntime(String runtime) {
        Runtime = runtime;
    }

    public void setTitle(String title) {
        Title = title;
    }

    public void setYear(String year) {
        Year = year;
    }
}
