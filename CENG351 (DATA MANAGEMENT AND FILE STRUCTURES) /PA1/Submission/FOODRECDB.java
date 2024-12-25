package ceng.ceng351.foodrecdb;

import javax.xml.transform.Result;
import java.awt.*;
import java.sql.*;
import java.util.ArrayList;

public class FOODRECDB implements  IFOODRECDB{

    private static String user = "e2449783";
    private static String password = "";
    private static String host = "";
    private static String database = "";
    private static int port = 8080;

    private static Connection connection;
    @Override
    public void initialize() {
        String url = "jdbc:mysql://" + this.host + ":" + this.port + "/" + this.database;

        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            this.connection =  DriverManager.getConnection(url, this.user, this.password);
        } catch (SQLException | ClassNotFoundException e) {
            e.printStackTrace();
        }
    }

    @Override
    public int createTables() {
        int numberOfCreatedTables = 0;

        String MenuItemsQuery = "CREATE TABLE IF NOT EXISTS MenuItems(" +
                "itemID int NOT NULL," +
                "itemName VARCHAR(40),"+
                "cuisine VARCHAR(20)," +
                "price INT," +
                "PRIMARY KEY (itemId))";


        String IngredientsQuery = "CREATE TABLE IF NOT EXISTS Ingredients(" +
                "ingredientID int NOT NULL," +
                "ingredientName VARCHAR(40),"+
                "PRIMARY KEY (ingredientID))";

        String IncludesQuery = "CREATE TABLE IF NOT EXISTS Includes(" +
                "itemID int," +
                "ingredientID INT,"+
                "PRIMARY KEY (itemID, ingredientID)," +
                "FOREIGN KEY (itemID) REFERENCES MenuItems(itemID),"+
                "FOREIGN KEY (ingredientID) REFERENCES Ingredients(ingredientID))";

        String RatingsQuery = "CREATE TABLE IF NOT EXISTS Ratings(" +
                "ratingID int NOT NULL," +
                "itemID INT,"+
                "rating INT," +
                "ratingDate DATE," +
                "PRIMARY KEY (ratingID)," +
                "FOREIGN KEY (itemID) REFERENCES MenuItems(itemID) )";

        String DietaryCategoriesQuery = "CREATE TABLE IF NOT EXISTS DietaryCategories(" +
                "ingredientID int NOT NULL," +
                "dietaryCategory VARCHAR(20) NOT NULL,"+
                "PRIMARY KEY (ingredientID, dietaryCategory)," +
                "FOREIGN KEY (ingredientID) REFERENCES Ingredients(ingredientID) )";

        String[] tables = {MenuItemsQuery,IngredientsQuery, IncludesQuery, RatingsQuery, DietaryCategoriesQuery};
        try {
            for(int i =0;i<tables.length;i++)
            {
                Statement statement = this.connection.createStatement();

                //Player Table
                int result = statement.executeUpdate(tables[i]);
                //System.out.println(result);
                numberOfCreatedTables++;

                //close
                statement.close();
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return numberOfCreatedTables;
    }

    @Override
    public int dropTables() {
        int numberOfDroppedTables = 0;

        String MenuItemsQuery = "DROP TABLE MenuItems";

        String IngredientsQuery = "DROP TABLE Ingredients";

        String IncludesQuery = "DROP TABLE Includes";

        String RatingsQuery = "DROP TABLE Ratings";

        String DietaryCategoriesQuery = "DROP TABLE DietaryCategories";

        String[] tables = {IncludesQuery, RatingsQuery, DietaryCategoriesQuery, MenuItemsQuery,IngredientsQuery};
        try {
            for(int i =0;i<tables.length;i++)
            {
                Statement statement = this.connection.createStatement();

                //Player Table
                int result = statement.executeUpdate(tables[i]);
                //System.out.println(result);
                numberOfDroppedTables++;

                //close
                statement.close();
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return numberOfDroppedTables;
    }

    @Override
    public int insertMenuItems(MenuItem[] items) {
        int numberOfInsertedRows = 0;
        for(int i=0;i<items.length;i++)
        {
            MenuItem item = items[i];

            String query = "INSERT INTO MenuItems values ('" +
                    item.getItemID()+ "','" +
                    item.getItemName() + "','" +
                    item.getCuisine() + "','" +
                    item.getPrice() +  "')";
            numberOfInsertedRows++;

            try {
                Statement st = this.connection.createStatement();
                int result = st.executeUpdate(query);
                //System.out.println(result);

                //Close
                st.close();

            } catch (SQLException e) {
                e.printStackTrace();
            }

        }


        return numberOfInsertedRows;
    }

    @Override
    public int insertIngredients(Ingredient[] ingredients) {
        int numberOfInsertedRows = 0;
        for(int i=0;i<ingredients.length;i++)
        {
            Ingredient ingredient = ingredients[i];

            String query = "INSERT INTO Ingredients values ('" +
                    ingredient.getIngredientID()+ "','" +
                    ingredient.getIngredientName() +  "')";
            numberOfInsertedRows++;


            try {
                Statement st = this.connection.createStatement();
                int result = st.executeUpdate(query);
                //System.out.println(result);

                //Close
                st.close();

            } catch (SQLException e) {
                e.printStackTrace();
            }
        }

        return numberOfInsertedRows;
    }

    @Override
    public int insertIncludes(Includes[] includes) {
        int numberOfInsertedRows = 0;
        for(int i=0;i<includes.length;i++)
        {
            Includes include = includes[i];

            String query = "INSERT INTO Includes values ('" +
                    include.getItemID()+ "','" +
                    include.getIngredientID() +  "')";
            numberOfInsertedRows++;


            try {
                Statement st = this.connection.createStatement();
                int result = st.executeUpdate(query);
                //System.out.println(result);

                //Close
                st.close();

            } catch (SQLException e) {
                e.printStackTrace();
            }
        }

        return numberOfInsertedRows;
    }

    @Override
    public int insertDietaryCategories(DietaryCategory[] categories) {
        int numberOfInsertedRows = 0;
        for(int i=0;i<categories.length;i++)
        {
            DietaryCategory category = categories[i];

            String query = "INSERT INTO DietaryCategories values ('" +
                    category.getIngredientID()+ "','" +
                    category.getDietaryCategory() +  "')";
            numberOfInsertedRows++;


            try {
                Statement st = this.connection.createStatement();
                int result = st.executeUpdate(query);
                //System.out.println(result);

                //Close
                st.close();

            } catch (SQLException e) {
                e.printStackTrace();
            }
        }

        return numberOfInsertedRows;
    }

    @Override
    public int insertRatings(Rating[] ratings) {
        int numberOfInsertedRows = 0;
        for(int i=0;i<ratings.length;i++)
        {
            Rating rating = ratings[i];

            String query = "INSERT INTO Ratings values ('" +
                    rating.getRatingID()+ "','" +
                    rating.getItemID()+ "','" +
                    rating.getRating()+ "','" +
                    rating.getRatingDate() +  "')";
            numberOfInsertedRows++;


            try {
                Statement st = this.connection.createStatement();
                int result = st.executeUpdate(query);
                //System.out.println(result);

                //Close
                st.close();

            } catch (SQLException e) {
                e.printStackTrace();
            }
        }

        return numberOfInsertedRows;
    }

    @Override
    public MenuItem[] getMenuItemsWithGivenIngredient(String name) {
        ResultSet rs;
        ArrayList<MenuItem> items = new ArrayList<MenuItem>();

        String query = String.format("SELECT DISTINCT M.itemID, M.itemName, M.cuisine, M.price FROM MenuItems M, Ingredients I, Includes C WHERE I.ingredientName = '%s' AND C.ingredientID = I.ingredientID AND M.itemID = C.itemID ORDER BY M.itemID ASC;",name);

        try {
            Statement st = this.connection.createStatement();
            rs = st.executeQuery(query);


            while(rs.next())
            {

                int m_itemId = rs.getInt("itemID");
                String m_itemName = rs.getString("itemName");
                String m_cuisine = rs.getString("cuisine");
                int m_price = rs.getInt("price");

                MenuItem item = new MenuItem(m_itemId,m_itemName,m_cuisine,m_price);
                items.add(item);
            }
            //Close
            st.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }

        MenuItem[] result = new MenuItem[items.size()];
        result = items.toArray(result);

        return result;
    }

    @Override
    public MenuItem[] getMenuItemsWithoutAnyIngredient() {
        ResultSet rs;
        ArrayList<MenuItem> items = new ArrayList<MenuItem>();

        String query = "SELECT DISTINCT M.itemID, M.itemName, M.cuisine, M.price FROM MenuItems M WHERE M.itemID IN (SELECT K.itemID FROM MenuItems K WHERE K.itemID NOT IN (SELECT itemID FROM Includes)) ORDER BY M.itemID ASC;";

        try {
            Statement st = this.connection.createStatement();
            rs = st.executeQuery(query);


            while(rs.next())
            {

                int m_itemId = rs.getInt("itemID");
                String m_itemName = rs.getString("itemName");
                String m_cuisine = rs.getString("cuisine");
                int m_price = rs.getInt("price");

                MenuItem item = new MenuItem(m_itemId,m_itemName,m_cuisine,m_price);
                items.add(item);
            }
            //Close
            st.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }

        MenuItem[] result = new MenuItem[items.size()];
        result = items.toArray(result);

        return result;
    }

    @Override
    public Ingredient[] getNotIncludedIngredients() {
        ResultSet rs;
        ArrayList<Ingredient> items = new ArrayList<Ingredient>();

        String query = "SELECT DISTINCT I.ingredientID, I.ingredientName FROM Ingredients I WHERE I.ingredientID IN (SELECT K.ingredientID FROM Ingredients K WHERE K.ingredientID NOT IN (SELECT ingredientID FROM Includes)) ORDER BY I.ingredientID ASC;";

        try {
            Statement st = this.connection.createStatement();
            rs = st.executeQuery(query);


            while(rs.next())
            {

                int m_ingredientId = rs.getInt("ingredientID");
                String m_ingredientName = rs.getString("ingredientName");

                Ingredient item = new Ingredient(m_ingredientId,m_ingredientName);
                items.add(item);
            }
            //Close
            st.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }

        Ingredient[] result = new Ingredient[items.size()];
        result = items.toArray(result);

        return result;
    }

    @Override
    public MenuItem getMenuItemWithMostIngredients() {
        ResultSet rs;
        MenuItem result = null;

        String query = "SELECT M.itemID,M.itemName,M.cuisine,M.price\n" +
                "FROM MenuItems M, Ingredients I, Includes C\n" +
                "WHERE M.itemID=C.itemID and I.ingredientID=C.ingredientId\n" +
                "GROUP BY M.itemID\n" +
                "HAVING COUNT(*) =   (SELECT MAX(S.num) from (SELECT COUNT(*) num\n" +
                "FROM MenuItems M1, Ingredients I1, Includes C1\n" +
                "WHERE M1.itemID=C1.itemID and I1.ingredientID=C1.ingredientId\n" +
                "GROUP BY M1.itemID) as S) ;";
        try {
            Statement st = this.connection.createStatement();
            rs = st.executeQuery(query);


            rs.next();

                int m_itemId = rs.getInt("itemID");
                String m_itemName = rs.getString("itemName");
                String m_cuisine = rs.getString("cuisine");
                int m_price = rs.getInt("price");

                result = new MenuItem(m_itemId,m_itemName,m_cuisine,m_price);
            //Close
            st.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }


        return result;
    }

    @Override
    public QueryResult.MenuItemAverageRatingResult[] getMenuItemsWithAvgRatings() {
        ResultSet rs;
        ArrayList<QueryResult.MenuItemAverageRatingResult> items = new ArrayList<QueryResult.MenuItemAverageRatingResult>();

        String query = "SELECT M.itemID,M.itemName, AVG(R.rating) as A\n" +
                "FROM MenuItems M NATURAL LEFT OUTER JOIN Ratings R\n" +
                "GROUP BY M.itemID \n" +
                "ORDER BY AVG(R.rating) DESC;";
        try {
            Statement st = this.connection.createStatement();
            rs = st.executeQuery(query);


            while(rs.next())
            {

                String m_itemId = String.valueOf(rs.getInt("itemID"));
                String m_itemName = rs.getString("itemName");
                String m_avgRating = rs.getString("A");
                if(rs.wasNull()) m_avgRating ="null";

                QueryResult.MenuItemAverageRatingResult item = new QueryResult.MenuItemAverageRatingResult(m_itemId,m_itemName,m_avgRating);
                items.add(item);
            }
            //Close
            st.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }

        QueryResult.MenuItemAverageRatingResult[] result = new QueryResult.MenuItemAverageRatingResult[items.size()];
        result = items.toArray(result);

        return result;
    }

    @Override
    public MenuItem[] getMenuItemsForDietaryCategory(String category) {
        ResultSet rs;
        ArrayList<MenuItem> items = new ArrayList<MenuItem>();

        String query = String.format("SELECT DISTINCT M.itemID, M.itemName, M.cuisine, M.price\n" +
                "FROM DietaryCategories D ,MenuItems M, Ingredients I, Includes C \n" +
                "WHERE M.itemID = C.itemID and C.ingredientID = I.ingredientID and I.ingredientID = D.ingredientID and D.dietaryCategory = 'vegetarian'\n" +
                "GROUP BY M.itemID\n" +
                "HAVING COUNT(*) = (\n" +
                "    SELECT COUNT(*)\n" +
                "    FROM Includes I\n" +
                "    WHERE I.itemID = M.itemID\n" +
                ")\n" +
                "ORDER BY M.itemID ASC;",category);

        try {
            Statement st = this.connection.createStatement();
            rs = st.executeQuery(query);


            while(rs.next())
            {

                int m_itemId = rs.getInt("itemID");
                String m_itemName = rs.getString("itemName");
                String m_cuisine = rs.getString("cuisine");
                int m_price = rs.getInt("price");

                MenuItem item = new MenuItem(m_itemId,m_itemName,m_cuisine,m_price);
                items.add(item);
            }
            //Close
            st.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }

        MenuItem[] result = new MenuItem[items.size()];
        result = items.toArray(result);

        return result;
    }

    @Override
    public Ingredient getMostUsedIngredient() {
        ResultSet rs;
        Ingredient result = null;

        String query = "SELECT I.ingredientID,I.ingredientName\n" +
                "FROM Ingredients I, Includes C\n" +
                "WHERE I.ingredientID= C.ingredientID\n" +
                "GROUP BY I.ingredientID\n" +
                "HAVING COUNT(*) = (SELECT MAX(S.num) from (SELECT COUNT(*) num\n" +
                "FROM Ingredients I1, Includes C1\n" +
                "WHERE I1.ingredientID = C1.ingredientID\n" +
                "GROUP BY I1.ingredientID) as S)\n" +
                ";";

        try {
            Statement st = this.connection.createStatement();
            rs = st.executeQuery(query);


            rs.next();

            int m_ingredientId = rs.getInt("ingredientID");
            String m_ingredientName = rs.getString("ingredientName");

            result = new Ingredient(m_ingredientId,m_ingredientName);
            //Close
            st.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }


        return result;

    }

    @Override
    public QueryResult.CuisineWithAverageResult[] getCuisinesWithAvgRating() {
        ResultSet rs;
        ArrayList<QueryResult.CuisineWithAverageResult> items = new ArrayList<QueryResult.CuisineWithAverageResult>();

        String query = "SELECT DISTINCT M.cuisine, AVG(R.rating) as A\n" +
                "FROM MenuItems M NATURAL LEFT OUTER JOIN Ratings R\n" +
                "GROUP BY M.cuisine\n" +
                "ORDER BY AVG(R.rating) DESC;";
        try {
            Statement st = this.connection.createStatement();
            rs = st.executeQuery(query);


            while(rs.next())
            {

                String m_itemId = String.valueOf(rs.getString("cuisine"));
                String m_avgRating = rs.getString("A");
                if(rs.wasNull()) m_avgRating ="null";

                QueryResult.CuisineWithAverageResult item = new QueryResult.CuisineWithAverageResult(m_itemId,m_avgRating);
                items.add(item);
            }
            //Close
            st.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }

        QueryResult.CuisineWithAverageResult[] result = new QueryResult.CuisineWithAverageResult[items.size()];
        result = items.toArray(result);

        return result;
    }

    @Override
    public QueryResult.CuisineWithAverageResult[] getCuisinesWithAvgIngredientCount() {

        ResultSet rs;
        ArrayList<QueryResult.CuisineWithAverageResult> items = new ArrayList<QueryResult.CuisineWithAverageResult>();

        String query = "SELECT K.cuisine, AVG(ingredient_count) as A\n" +
                "FROM (\n" +
                "  SELECT M.cuisine, COUNT(C.ingredientID) as ingredient_count\n" +
                "  FROM MenuItems M LEFT JOIN Includes C ON M.itemID = C.itemID\n" +
                "  GROUP BY M.itemID ) as K\n" +
                "GROUP BY K.cuisine\n" +
                "ORDER BY A DESC;\n";
        try {
            Statement st = this.connection.createStatement();
            rs = st.executeQuery(query);


            while(rs.next())
            {

                String m_itemId = String.valueOf(rs.getString("cuisine"));
                String m_avgRating = rs.getString("A");
                QueryResult.CuisineWithAverageResult item = new QueryResult.CuisineWithAverageResult(m_itemId,m_avgRating);
                items.add(item);
            }
            //Close
            st.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }

        QueryResult.CuisineWithAverageResult[] result = new QueryResult.CuisineWithAverageResult[items.size()];
        result = items.toArray(result);

        return result;
    }

    @Override
    public int increasePrice(String ingredientName, String increaseAmount) {
        int rs = 0;
        ArrayList<QueryResult.CuisineWithAverageResult> items = new ArrayList<QueryResult.CuisineWithAverageResult>();

        String query = String.format("UPDATE MenuItems\n" +
                "SET price = price + %s\n" +
                "WHERE itemID IN (\n" +
                "SELECT C.itemID\n" +
                "FROM Includes C, Ingredients I\n" +
                "WHERE C.ingredientID = I.ingredientID and I.ingredientName = '%s');",increaseAmount,ingredientName);
        try {
            Statement st = this.connection.createStatement();
            rs = st.executeUpdate(query);
            //Close
            st.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }


        return rs;
    }

    @Override
    public Rating[] deleteOlderRatings(String date) {
        ResultSet rs;
        ArrayList<Rating> ratings = new ArrayList<Rating>();

        String query1 = String.format("SELECT ratingID,itemID,rating,ratingDate FROM Ratings WHERE ratingDate < '%s'", date);
        String query2 = String.format("DELETE FROM Ratings WHERE ratingDate < '%s'", date);

        try {
            Statement st = this.connection.createStatement();
            rs = st.executeQuery(query1);


            while(rs.next())
            {

                int m_ratingId = rs.getInt("ratingID");
                int m_itemId = rs.getInt("itemID");
                int m_rating = rs.getInt("rating");
                String m_ratingDate = String.valueOf(rs.getDate("ratingDate"));

                Rating rating = new Rating(m_ratingId,m_itemId,m_rating,m_ratingDate);
                ratings.add(rating);
            }
            st.close();

            Statement st1 = this.connection.createStatement();;
            st1.executeUpdate(query2);
            st1.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }

        Rating[] result = new Rating[ratings.size()];
        result = ratings.toArray(result);

        return result;

    }
}
