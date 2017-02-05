import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Calendar;
import java.sql.*;
import java.io.*;

public class SalesSystem {
  public static void promptEnterKey(){
    System.out.println("Press \"ENTER\" to continue...");
    try {
      int read = System.in.read(new byte[2]);
    } catch (IOException e) {
      e.printStackTrace();
    }
  }

  public static void mainInterface(Statement stmt) {
   String mainMenuMsg = "-----Main menu-----\n"+
   "What kinds of operations would you like to perform\n"+
   "1. Operations for administrator\n"+
   "2. Operations for salesperson\n"+
   "3. Operations for manager\n"+
   "4. Exit this program\n"+
   "Enter Your Choice:";
   String errInput = "Invalid input...please retry!\n";
   System.out.println(mainMenuMsg);

   BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
   String str;
   int input = 0;
   try {
     str = in.readLine();
     input = Integer.parseInt(str);
   } catch(IOException e) {
     System.err.println(e);
   }

   switch (input){
     case 1:
     adminInterface(stmt);
     break;
     case 2:
     salesInterface(stmt);
     break;
     case 3:
     managerInterface(stmt);
     break;
     case 4:
     break;
     default:
     System.out.println(errInput);
     mainInterface(stmt);
     break;
   }
 }

 public static void adminInterface(Statement stmt) {
   String adminMenuMsg = "-----Operations for administrator menu-----\n"+
   "What kinds of operations would you like to perform\n"+
   "1. Create all tables\n"+
   "2. Delete all tables\n"+
   "3. Load from datafile\n"+
   "4. Show number of records in each table\n"+
   "5. Return to the main menu\n"+
   "Enter Your Choice:";

   String errInput = "Invalid input...please retry!\n";
   String commandstart="Process...";
   System.out.println(adminMenuMsg);
   BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
   String str;
   int input = 0;
   try {
     str = in.readLine();
     input = Integer.parseInt(str);
   } catch(IOException e) {
     System.err.println(e);
   }
   try{
     switch (input){
       case 1:
       System.out.println(commandstart);
       stmt.executeUpdate("DROP TABLE IF EXISTS transaction");
       stmt.executeUpdate( "DROP TABLE IF EXISTS part");
       stmt.executeUpdate("DROP TABLE IF EXISTS category");
       stmt.executeUpdate("DROP TABLE IF EXISTS manufacturer");
       stmt.executeUpdate("DROP TABLE IF EXISTS salesperson");
       stmt.executeUpdate("CREATE TABLE category(cID INTEGER, cName CHAR(255), PRIMARY KEY(cID))");
       stmt.executeUpdate("CREATE TABLE manufacturer(mID INTEGER, mName CHAR(255), mAddress CHAR(255), mPhoneNumber INTEGER, PRIMARY KEY(mID))");
       stmt.executeUpdate("CREATE TABLE part(pID INTEGER, pName CHAR(255), pPrice INTEGER, mID INTEGER, cID INTEGER, pWarrantyPeriod INTEGER, pAvailableQuantity INTEGER,  PRIMARY KEY(pID), FOREIGN KEY(mID) REFERENCES manufacturer(mID), FOREIGN KEY(cID) REFERENCES category(cID))");
       stmt.executeUpdate("CREATE TABLE salesperson(sID INT, sName CHAR(255), sAddress CHAR(255), sPhoneNumber INT, sExperience INT, PRIMARY KEY(sID))");
       stmt.executeUpdate("CREATE TABLE transaction(tID INT, pID INT, sID INT, tDate DATE, PRIMARY KEY(tID), FOREIGN KEY(pID) REFERENCES part(pID), FOREIGN KEY(sID) REFERENCES salesperson(sID))");
       String createfinished="Done!Database is initialized!";
       System.out.println(createfinished);
       promptEnterKey();
       adminInterface(stmt);
       break;
       case 2:
       System.out.println(commandstart);
       stmt.executeUpdate("DROP TABLE IF EXISTS transaction");
       stmt.executeUpdate( "DROP TABLE IF EXISTS part");
       stmt.executeUpdate("DROP TABLE IF EXISTS category");
       stmt.executeUpdate("DROP TABLE IF EXISTS manufacturer");
       stmt.executeUpdate("DROP TABLE IF EXISTS salesperson");
       String deletefinished="Done! Database is removed";
       System.out.println(deletefinished);
       promptEnterKey();
       adminInterface(stmt);
       break;
       case 3:
       System.out.println(commandstart);
       String path= "'./sample_data/";
       stmt.executeUpdate("LOAD DATA LOCAL INFILE "+ path + "category.txt'" + " into table category");
       stmt.executeUpdate("LOAD DATA LOCAL INFILE "+ path + "manufacturer.txt'" + " into table manufacturer");
       stmt.executeUpdate("LOAD DATA LOCAL INFILE "+ path + "part.txt'" + " into table part");
       stmt.executeUpdate("LOAD DATA LOCAL INFILE "+ path + "salesperson.txt'" + " into table salesperson");
       stmt.executeUpdate("LOAD DATA LOCAL INFILE "+ path + "transaction.txt'" + " into table transaction LINES TERMINATED BY '\n' (tID, pID, sID, @var1) SET tDate = STR_TO_DATE(@var1, '%d/%m/%Y')");

       String loadfinished="Done! Data is inputted to the database!";
       System.out.println(loadfinished);
       promptEnterKey();
       adminInterface(stmt);
       break;
       case 4:
       String showfinished="Number of records in each table:";
       System.out.println(showfinished);
 					//get the result of category
       ResultSet rs = stmt.executeQuery("Select count(*) from category");
       String count= "Unknown";
       rs.next();
       count = rs.getString(1);
       System.out.print("category:");
       System.out.println(count);

 					//get the result of manufacturer
       rs = stmt.executeQuery("Select count(*) from manufacturer");
       rs.next();
       count = rs.getString(1);
       System.out.print("manufacturer:");
       System.out.println(count);

 					//get the result of part
       rs = stmt.executeQuery("Select count(*) from part");
       rs.next();
       count = rs.getString(1);
       System.out.print("part:");
       System.out.println(count);

 					//get the result of salesperson
       rs = stmt.executeQuery("Select count(*) from salesperson");
       rs.next();
       count = rs.getString(1);
       System.out.print("salesperson:");
       System.out.println(count);

 					//get te result of transaction
       rs = stmt.executeQuery("Select count(*) from transaction");
       rs.next();
       count = rs.getString(1);
       System.out.print("trasaction:");
       System.out.println(count);
       promptEnterKey();
       adminInterface(stmt);
       break;
       case 5:
       mainInterface(stmt);
       break;
       default:
       System.out.println(errInput);
       adminInterface(stmt);
       break;
     }
   } catch (SQLException e){
     System.err.println(e);
   }
 }

 public static void salesInterface(Statement stmt) {
  String salesMenuMsg = "-----Operations for salesperson menu-----\n"+
  "What kinds of operations would you like to perform\n"+
  "1. Search for parts\n"+
  "2. Sell a part\n"+
  "3. Return to the main menu\n"+
  "Enter Your Choice:";

  String errInput = "Invalid input...please retry!\n";

  System.out.println(salesMenuMsg);
  BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
  String str;
  int input = 0;
  try {
   str = in.readLine();
   input = Integer.parseInt(str);
 } catch(IOException e) {
   System.err.println(e);
 }
 try{
  switch (input){
   case 1:{
    String key = "null";
    int order=0; int choice =0;

                    //get the selectmesg (1 or 2) and store it in (choice)
    String selectmesg="Choose the search criterion:\n"+
    "1. Part Name\n"+
    "2. Manufacturer Name\n"+
    "Choose the search criterion: ";
    System.out.print(selectmesg);
    try {
     str = in.readLine();
     choice = Integer.parseInt(str);
   } catch(IOException e) {
     System.err.println(e);
   }

                     //get the key word and store it in (str)
   String requestkey="Type in the Search Key Word: ";
   System.out.print(requestkey);
   try {
     key = in.readLine();
   } catch(IOException e) {
     System.err.println(e);
   }

 					//get the ordering and store it in (order)
   String requestorder="Choose ordering:\n"+"1. By price, ascending order\n"+"2. By price, descending order\n"+"Choose the search criterion: ";
   System.out.print(requestorder);
   try {
    str = in.readLine();
    order = Integer.parseInt(str);
  } catch(IOException e) {
    System.err.println(e);
  }
  System.out.println(choice+" "+order);
  ResultSet rs=null;
 					//search
  switch(choice){
    case 1:
    switch(order){
     case 1:
     rs = stmt.executeQuery("SELECT P.pID, P.pName, M.mName, C.cName, P.pAvailableQuantity, P.pWarrantyPeriod, P.pPrice "+
       "from part P, manufacturer M, category C "+
       "where P.mID=M.mID AND P.cID=C.cID AND P.pName LIKE "+ "\"%" +
       key +
       "%\" order by P.pPrice asc");
     break;
     case 2:
     rs = stmt.executeQuery("SELECT P.pID, P.pName, M.mName, C.cName, P.pAvailableQuantity, P.pWarrantyPeriod, P.pPrice "+
       "from part P, manufacturer M, category C "+
       "where P.mID=M.mID AND P.cID=C.cID AND P.pName LIKE "+ "\"%" +
       key +
       "%\" order by P.pPrice desc");
     break;
     default:
     System.out.println(errInput);
     salesInterface(stmt);
     break;
   }
   break;
   case 2:
   switch(order){
    case 1:
    rs = stmt.executeQuery("SELECT P.pID, P.pName, M.mName, C.cName, P.pAvailableQuantity, P.pWarrantyPeriod, P.pPrice "+
     "from part P, manufacturer M, category C "+
     "where P.mID=M.mID AND P.cID=C.cID AND M.mName LIKE "+ "\"%" +
     key +
     "%\" order by P.pPrice asc");
    break;
    case 2:
    rs = stmt.executeQuery("SELECT P.pID, P.pName, M.mName, C.cName, P.pAvailableQuantity, P.pWarrantyPeriod, P.pPrice "+
     "from part P, manufacturer M, category C "+ 
     "where P.mID=M.mID AND P.cID=C.cID AND M.mName LIKE "+ "\"%" +
     key +
     "%\" order by P.pPrice desc");
    break;
    default:
    System.out.println(errInput);
    salesInterface(stmt);
    break;
  }
  break;

  default:
                         //System.out.println(1.3);
  System.out.println(errInput);
  salesInterface(stmt);
  break;	
}
String schema = "| ID | Name | Manufacturer | Category | Quantity | Warranty | Price |";
System.out.println(schema);
while(rs.next()) {
  System.out.print("| "+ rs.getInt("pID") + " ");
  System.out.print("| "+ rs.getString("pName") + " ");
  System.out.print("| "+ rs.getString("mName") + " ");
  System.out.print("| "+ rs.getString("cName") + " ");
  System.out.print("| "+ rs.getInt("pAvailableQuantity") + " ");
  System.out.print("| "+ rs.getInt("pWarrantyperiod") + " ");
  System.out.println("| "+ rs.getInt("pPrice") + " |");
}
String endmesg="End of Query";
System.out.println(endmesg);
promptEnterKey();
salesInterface(stmt);
break;
}
case 2:
String requestpartID = "Enter the part ID:";
System.out.print(requestpartID);
int ID1 = 0;
try{
  str = in.readLine();
  ID1 = Integer.parseInt(str);
}catch(IOException e){
  System.err.println(e);
}
String requestsalesID = "Enter the salesperson ID:";
System.out.print(requestsalesID);
int ID2 = 0;
try{
  str = in.readLine();
  ID2 = Integer.parseInt(str);
}catch(IOException e){
  System.err.println(e);
}
ResultSet rs;
int remain = 0;
rs = stmt.executeQuery("SELECT * FROM salesperson S WHERE S.sID =" + ID2);
if (!rs.next()){
  System.out.println("Sorry, this salesperson does not exist.");
  promptEnterKey();
  salesInterface(stmt);
} 
rs = stmt.executeQuery("SELECT P.pAvailableQuantity, P.pName from part P where P.pID=" + ID1);
if (rs.next()){
  remain = rs.getInt(1);
  String tempname = rs.getString(2);
  String pro="Product: "+ tempname; String rem="Remaining quantity: "; String tempid="(id: "+ ID1 +") ";
  if (remain!=0){
    stmt.executeUpdate("UPDATE part SET pAvailableQuantity=pAvailableQuantity-1 where pID=" + ID1);
    rs=stmt.executeQuery("SELECT MAX(T.tID) from transaction T");
    int newID = 0;
    rs.next();
    newID = rs.getInt(1)+1;
    /*
    DateFormat dateFormat = new SimpleDateFormat("dd/MM/yyyy");
    java.sql.Date date = new java.sql.Date(Calendar.getInstance().getTime().getTime());
    dateFormat.format(date);
    */
    stmt.executeUpdate("INSERT into transaction (tID, pID, sID, tDate) VALUES ("+ newID + ", "+ ID1+", " + ID2+", " +"CurDate()"+")");
    remain=remain-1;
    System.out.println(pro+tempid+rem+remain);
  }
  else{
    String sellout = "Nothing left!!!";
    System.err.println(sellout);
  }
}
else {
  System.out.println("We don't sell this part.");
}
promptEnterKey();
salesInterface(stmt);
break;
case 3:
mainInterface(stmt);
break;
default:
System.out.println(errInput);
salesInterface(stmt);
break;
}
}catch (SQLException e){
 System.err.println(e);
}
}
public static void managerInterface(Statement stmt) {
  String managerMenuMsg = "-----Operations for manager menu-----\n"+
  "What kinds of operations would you like to perform\n"+
  "1. Count the no. of sales record of each salesperson under a specific range on years of experience\n"+
  "2. Show the total sales value of each manufacturer\n"+
  "3. Show the N most popular part\n"+
  "4. Return to the main menu\n"+
  "Enter Your Choice:";

  String errInput = "Invalid input...please retry!\n";

  System.out.println(managerMenuMsg);
  BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
  String str;
  int input = 0;
  try {
   str = in.readLine();
   input = Integer.parseInt(str);
 } catch(IOException e) {
   System.err.println(e);
 }
 String schema=null;
 String endmesg="End of query";
 ResultSet rs = null;
 try{
   switch (input){
     case 1:
     int lowerbd=0; int upperbd=0;
     String requestlbd="Type in the lower bound for years of experience: ";
     System.out.print(requestlbd);
     try {
      str = in.readLine();
      lowerbd = Integer.parseInt(str);
    } catch(IOException e) {
      System.err.println(e);
    }
    String requestubd="Type in the upper bound for years of experience: ";
    System.out.print(requestubd);
    try {
      str = in.readLine();
      upperbd = Integer.parseInt(str);
    } catch(IOException e) {
      System.err.println(e);
    }
    String answer1="Transaction Record: ";
    System.out.println(answer1);
    schema = "| ID | Name | Year of Experience | Number of Transaction |";
    System.out.println(schema);
    rs = stmt.executeQuery("SELECT S.sID, S.sName, S.sExperience, temp.number from salesperson S, (Select T.sID, count(*) as number from transaction T group by T.sID ) as temp where S.sExperience>= " + lowerbd +
     " AND S.sExperience<=" + upperbd + " AND temp.sID=S.sID order by S.sID desc");
    int chosensid=0;
    while(rs.next()) {
      chosensid = rs.getInt("sID");
      System.out.print("| "+ rs.getString("sID") + " ");
      System.out.print("| "+ rs.getString("sName") + " ");
      System.out.print("| "+ rs.getString("sExperience") + " ");
      System.out.println("| "+ rs.getString("number") + " |");
    }
    System.out.println(endmesg);
    promptEnterKey();
    managerInterface(stmt);
    break;
    case 2:
    schema = "| Manufacturer ID | Manufacturer Name | Total Sales Value |";
    System.out.println(schema);
    rs = stmt.executeQuery("SELECT M.mID, M.mName, tempb.total "+
      "from (Select P.mID, sum(tempa.sales) as total from (Select P1.pID, temp.number*P1.pPrice as sales from (Select T.pID, count(*) as number from transaction T group by T.pID) as temp," +
      " part P1 where temp.pID=P1.pID) as tempa, part P "+
      "where P.pID = tempa.pID group by P.mID) as tempb, manufacturer M "+
      "where M.mID = tempb.mID order by tempb.total desc");
    while(rs.next()) {
      System.out.print("| "+ rs.getString("mID") + " ");
      System.out.print("| "+ rs.getString("mName") + " ");
      System.out.println("| "+ rs.getString("total") + " |");
    }
    System.out.println(endmesg);
    promptEnterKey();
    managerInterface(stmt);
    break;
    case 3:
    String typenumber = "Type ine the number of parts: ";
    System.out.println(typenumber);
    int numberofparts = 0;
    try {
      str = in.readLine();
      numberofparts = Integer.parseInt(str);
    } catch(IOException e) {
      System.err.println(e);
    }
    if (numberofparts > 0){
     schema="|  Part ID | Part Name | No. of Transaction |";
     System.out.println(schema);
     rs = stmt.executeQuery("Select P.pID, P.pName, temp.number from (Select T.pID, count(*) as number from transaction T group by T.pID) as temp, part P "+
       "where temp.pID=P.pID order by temp.number desc limit "+ numberofparts);
     while(rs.next()){
       System.out.print("| " + rs.getString("pID") + " " );
       System.out.print("| " + rs.getString("pName") + " " );
       System.out.println("| " + rs.getString("number") + " |" );
     }
     System.out.println(endmesg);
   }
   promptEnterKey();
   managerInterface(stmt);
   break;
   case 4:
   mainInterface(stmt);
   break;
   default:
   System.out.println(errInput);
   managerInterface(stmt);
   break;
 }
}catch (SQLException e){
  System.err.println(e);
}
}

public static void main(String[] args){

 try {
  Class.forName("com.mysql.jdbc.Driver");
} catch(Exception x) {
  System.err.println("Unable to load the driver class!");
}

try {
  Connection conn = DriverManager.getConnection("jdbc:mysql://projgw.cse.cuhk.edu.hk:2712/db25?autoReconnect=true&useSSL=false", "db25", "f908dde3");
  Statement stmt = conn.createStatement();

 			//drop all existing tables
 			//stmt.executeUpdate("DROP TABLE IF EXISTS");

 			//add sample-data

 			//enter maininterface
  String welcomeMsg = "Welcome to sales system!\n\n";
  System.out.println(welcomeMsg);
  mainInterface(stmt);
} catch (Exception e) {
  e.printStackTrace();
}
}
}
