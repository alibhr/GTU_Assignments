package DataStructureHW6_Q3;

import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

/**
 * The Library automation system
 */
public class LibraryAutomationSystem {
    /**
     * The admin of the system
     */
    private Administrator admin;

    /**
     * The locations of the Books.
     */
    private Map<String, Map<String,Set<String>>> locations;

    /**
     * creates a new library automation system.
     */
    public LibraryAutomationSystem(){
        locations = new HashMap<String,Map<String,Set<String>>>();
        admin = new Administrator("Ali","Bahar","171044066");
    }

    /**
     * prints the all books of the author that given as parameter.
     * @param authorName author name to be searched.
     */
    public void searchByAuthorName(String authorName){
        Map<String,Set<String>> books = locations.get(authorName);

        if(books == null)
            return;

        for (String bookTitle : books.keySet()) {
            System.out.println(bookTitle);
        }
    }

    /**
     * displays the all locations of the book
     * @param authorName author of the book to be searched.
     * @param bookTitle the book name to be searched.
     */
    public void displayTheLocations(String authorName,String bookTitle){
        Map<String,Set<String>> books = locations.get(authorName);
        if(books == null)
            return;

        Set<String> localLocations = books.get(bookTitle);
        if(localLocations == null)
            return;

        for(String l: localLocations){
            System.out.println(l);
        }
    }

    /**
     * finds the all information about the book.
     * @param bookTitle book name to be searched.
     */
    public void searchByBookTitle(String bookTitle){
        Map<String,Set<String>> books;
        for(String authorName : locations.keySet()){
            books = locations.get(authorName);
            Set<String> localLocations = books.get(bookTitle);
            if(localLocations != null){
                System.out.println("Author Name : " + authorName +"\nBook Title : " + bookTitle);
                for(String l: localLocations){
                    System.out.println("location " + l);
                }
            }
        }
    }

    /**
     * Adds a new book to system
     * @param newAuthor author of the new book
     * @param newTitle title of the new book
     * @param location location of the new book
     */
    public void addBook(String newAuthor, String newTitle,String location){
        if(!admin.isLogin())
            return;;

        Map<String,Set<String>> books = locations.get(newAuthor);
        if(books == null){
            Map<String,Set<String>> t = new HashMap<>();
            Set<String> l = new HashSet<>();
            l.add(location);
            t.put(newTitle,l);
            locations.put(newAuthor,t);
            return;
        }
        Set<String> l = books.get(newTitle);
        if(l == null){
            l = new HashSet<>();
            l.add(location);
            locations.get(newAuthor).put(newTitle,l);
        }else{
            l.add(location);
        }
    }

    /**
     * deletes the book from system.
     * @param bookTitle the title of the book to be removed.
     */
    public void deleteByTitle(String bookTitle){
        if(!admin.isLogin())
            return;;

        for(String authorName : locations.keySet()){
            Map<String,Set<String>> book = locations.get(authorName);
            Set<String> localLocations = book.get(bookTitle);
            if(localLocations != null){
                book.remove(bookTitle);
            }
        }
    }

    /**
     * deletes the book from system.
     * @param location the location of the book to be removed.
     */
    public void deleteByLocation(String location){
        if(!admin.isLogin())
            return;;

        for(String authorName : locations.keySet()){
            Map<String,Set<String>> books = locations.get(authorName);
            for(String bookName : books.keySet()){
                Set<String> l = books.get(bookName);
                if(l.remove(location)){
                    //System.out.println("removed");
                    return;
                }
            }
        }
    }

    /**
     * deletes all books of the author.
     * @param author the author name of the books to be removed.
     */
    public void deleteByAuthor(String author){
        if(!admin.isLogin())
            return;;

        Map<String,Set<String>> books = locations.get(author);
        if(books != null){
            locations.remove(author);
        }
    }

    /**
     * login is necessary to add book or remove book.
     * @param password the password to be able to log in to system.
     * @return true if login is success.
     */
    public boolean loginToSystemAsAdmin(String password){
        return admin.login(password);
    }
}