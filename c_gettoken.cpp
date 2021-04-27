# include <iostream>
# include <vector>
# include <string>
# include <sstream>
# include <string.h>
# include <vector>
# include <stdlib.h>
# include <stdio.h>
using namespace std ;

struct Token_data {
  string data  ;
  string type  ;  // math 
} ;

struct Id_Count {
  string id  ;
  string count  ; 
};

vector<Id_Count> g_id_count; 
vector<Token_data> g_calcu_v; 
vector<Token_data> g_scan ; 
vector<Token_data> g_alg; 

int g_ans ; 
int g_th ; 
int g_type = 3 ; 
char g_topic[5000] ; 
int g_at = 0 ; 
 
// ----------------for calcu
int g ; 
double g_final = 0 ; 


void Command() ; 
void IDlessArithExpOrBexp() ;
void BooleanOprator() ;
void NOT_ID_StartArithExpOrBexp() ;
void NOT_ID_StartArithExp() ;
void NOT_ID_StartTerm() ;
void NOT_ID_StartFactor() ;
void ArithExp() ;
void Term() ;
void Factor() ;   
bool g_quit = false ; 
bool g_first_token = false ; 
bool g_error_1 = false ; 
bool g_error_2 = false ; 
bool g_error_3 = false ; 
char g_error_char = '\0' ; 
double ArithExp2() ;
double Term2() ;
double Factor2() ; 


void String_to_int( string s, int &i ) { 
  stringstream ss;
  ss << s; 
  ss >> i;
} // String_to_int()

void String_to_double( string s, double &i ) { 
  stringstream ss;
  ss << s; 
  ss >> i;
} // String_to_double()

void Double_to_string( string &s, float i ) {
  stringstream ss;
  ss << i; 
  ss >> s;
} // Double_to_string()

void Float_to_string( string &s, float i ) {
  stringstream ss;
  ss << i; 
  ss >> s;
} // Float_to_string()

// --------------------deal-classify--------------------
bool Deal_boolean( string before, string boolean, string after ) {
  double before_int = 0 ; 
  double after_int = 0 ; 
  String_to_double( before, before_int ) ; 
  String_to_double( after, after_int ) ;
  
  if ( boolean == ">" ) {
    if ( before_int > after_int )
      return true;
    else 
      return false ; 
  } // if()
  
  if ( boolean == "<" ) {
    if ( before_int < after_int )
      return true;
    else 
      return false ; 
  } // if()  
  
  if ( boolean == "=" ) {
    if ( before_int == after_int )
      return true;
    else 
      return false ; 
  } // if() 
  
  if ( boolean == ">=" ) {
    if ( before_int >= after_int )
      return true;
    else 
      return false ; 
  } // if()
  
  if ( boolean == "<=" ) {
    if ( before_int <= after_int )
      return true;
    else 
      return false ; 
  } // if()
  
  return 0 ; 
} // Deal_boolean() 

void Change( int start ) {  

  for ( int i = 0 ; i < g_id_count.size() ; i++ ) {  // 有找到就代換 
    for ( int j = start ; j < g_calcu_v.size() ; j++ ) {
      if ( g_calcu_v.at( j ).data == g_id_count.at( i ).id ) {
        g_calcu_v.at( j ).data = g_id_count.at( i ).count;
        g_calcu_v.at( j ).type = "count" ; 
      } // if() 
    } // for() 
  } // for() 
  
  for ( int i = 0 ; i < g_calcu_v.size() ; i++ ) {
    if ( g_calcu_v.at( i ).type == "count" ) {
      if ( g_calcu_v.at( i ).data.at( 0 ) == '.' ) 
        g_calcu_v.at( i ).data = "0" + g_calcu_v.at( i ) .data ; 
    } // if()
  } // for()
  

} // Change()

void Update( string type1_id, string all_count, bool &find ) {
  for ( int i = 0 ; i < g_id_count.size() ; i++ ) {  // 有找到就代換 
    if ( type1_id == g_id_count.at( i ).id ) {
      g_id_count.at( i ).count = all_count;
      find = true ; 
    } // if() 
  } // for()  
} // Update()

void G_plus1() {
  if ( g < g_alg.size()- 1 ) g++ ; 
} // G_plus1()

bool Is_count() {
  int og = 0 ; 
  int sign = 0 ;
  int count = 0 ; 
  if ( g_alg.at( g + 1 ).data == "+" || g_alg.at( g + 1 ).data == "-" )  
    return true ; 
  else 
    return false ; 
} // Is_count()

double ArithExp2() { 
  cout << "ArithExp2 :" << g_alg.at(g).data << endl ; 
  double a_f = 0 ;
  a_f += Term2() ; 

  while ( g_alg.at( g ).data == "+" || g_alg.at( g ).data == "-" ) { 
    // cout << "ArithExp2 :" << g_alg.at(g).data << endl ; 
    if ( g_alg.at( g ).data == "+" ) {
      G_plus1();
      a_f += Term2() ;
    } // if()
    else if ( g_alg.at( g ).data == "-" ) {
      G_plus1();
      a_f -= Term2() ;
    } // else if()
  } // while()
  
  return a_f; 
} // ArithExp2()
  
double Term2() { 

  cout << "Term2 :" << g_alg.at(g).data << endl ; 
  double t_f = 0 ; 
  double count = 0 ;
  t_f = t_f + Factor2(); 
  
  while ( g_alg.at( g ).data == "*" || g_alg.at( g ).data == "/" ) {
    // cout << "Term2 :" << g_alg.at(g).data << endl ; 
    if ( g_alg.at( g ).data == "*" ) {
      if ( g_alg.at( g + 1 ).data == "+" ) {
        String_to_double( g_alg.at( g + 2 ).data, count ) ;
        t_f *= count ;
        G_plus1(); 
        G_plus1();
        G_plus1(); 
        return t_f ; 
      } // if()
      else if ( g_alg.at( g + 1 ).data == "-" ) {
        String_to_double( g_alg.at( g + 2 ).data, count ) ;
        t_f *= count ;
        t_f *= -1 ; 
        G_plus1(); 
        G_plus1();
        G_plus1(); 
        return t_f ; 
      } // else if 
      else {
        G_plus1();
        t_f *= Factor2();
      } // else()
    } // if()
    else if ( g_alg.at( g ).data == "/" ) {
      if ( g_alg.at( g + 1 ).data == "+" ) {
        String_to_double( g_alg.at( g + 2 ).data, count ) ;
        t_f /= count ;
        G_plus1(); 
        G_plus1();
        G_plus1();
        return t_f ; 
      } // if()
      else if ( g_alg.at( g + 1 ).data == "-" ) {
        String_to_double( g_alg.at( g + 2 ).data, count ) ;
        t_f /= count ;
        t_f *= -1 ; 
        G_plus1();
        G_plus1();
        G_plus1();
        return t_f ; 
      } // else if 
      else {
        G_plus1();
        t_f /= Factor2();
      } // else()
    } // if()
  } // while()
  
  return t_f ;
} // Term2()
              
double Factor2() { 
  cout << "Factor2 :" <<g_alg.at(g).data << endl ; 
  double d_f = 0 ;  

  if ( g_alg.at( g ).data == "(" ) {
    G_plus1(); 
    d_f += ArithExp2();
    
    if ( g_alg.at( g ).data == ")" ) { // 回來後要右括號 
      G_plus1();
      // cout << "有回來" << g_alg.at(g).data ;
    } // if()
    
    return d_f;
  } // if()
  else {
    if ( g_alg.at( g ).data != "+" && g_alg.at( g ).data != "-" ) {
      String_to_double( g_alg.at( g ).data, d_f ) ; 
      G_plus1();
    } // if() 
    else {
      /*
      if (g_alg.at( g ).data == "+" ){
        G_plus1();
        String_to_double( g_alg.at( g ).data, d_f ) ;
      }
      if (g_alg.at( g ).data == "-" ){
        G_plus1();
        g_alg.at( g ).data = "-" + g_alg.at( g ).data ; 
        String_to_double( g_alg.at( g ).data, d_f ) ;
      }
      */  
    } // else()
    
    return d_f; 
  } // else()
}  // Factor2()

// ----------------get_token_strart--------------------
void Math_take( Token_data &token, char &temp, char &next_temp ) {

  bool is_float = false; 
  bool already_float = false ; 
  token.data = token.data + g_topic[g_at] ; // 先家第一個數字 
  
  while ( ( g_topic[g_at+1] >= 48 && g_topic[g_at+1] <= 57 ) || g_topic[g_at+1] == '.' ) {
    
    if ( g_topic[g_at+1] == '.'  ) {   // 一串TOKEN只能有一個浮點數 
      if ( is_float == true )     // 報錯跳出 
        return ; 
      if ( is_float == false ) {  // 正常執行 
        is_float = true ; 
      } // if()
    } // if()
    
    token.data = token.data + g_topic[g_at+1] ;  
    g_at++;

  } // while()
} // Math_take()

void English_start( Token_data &token, char &temp, char &next_temp ) {
  bool jump = false ; 
  token.data = token.data + g_topic[g_at] ;
  while ( ( ( g_topic[g_at+1] >= 65 && g_topic[g_at+1] <= 90 ) 
            || ( g_topic[g_at+1] >= 97 && g_topic[g_at+1] <= 122 ) 
            || ( g_topic[g_at+1] >= 48 && g_topic[g_at+1] <= 57 ) 
            || ( g_topic[g_at+1] == '_' ) ) && jump == false ) {  // 為數字或者英文
    token.data = token.data + g_topic[g_at+1] ; 
    g_at++;
    // if ( temp == ' ' ) break ; 
    if  ( ( g_topic[g_at+1] >= 65 && g_topic[g_at+1] <= 90 ) 
          || ( g_topic[g_at+1] >= 97 && g_topic[g_at+1] <= 122 ) 
          || ( g_topic[g_at+1] >= 48 && g_topic[g_at+1] <= 59 ) || g_topic[g_at+1] == '_' ) 
    {
         
    } // if() 
    else {
      jump = true ; 
    } // else() 
  } // while()
} // English_start()

void Dot_first(  Token_data &token, char &temp, char &next_temp ) {
  
  token.type = "count" ;  
  token.data = g_topic[g_at-1] + token.data +g_topic[g_at] ; 
  
  while ( g_topic[g_at+1] >= 48 && g_topic[g_at+1] <= 57 ) {
    g_at++;
    token.data = token.data + g_topic[g_at] ; 
  } // while()
  
} // Dot_first()

void Get_token( Token_data &token, char &temp, char &next_temp, bool &at_next ) { 
  if ( at_next == false ) {
    g_at++;
    while ( g_topic[g_at] == ' ' ) g_at++ ; 
  } // if()
  else at_next = false ; 
  // 純數字 或 小數 
  
  
  if ( g_topic[g_at] == '/' ) {
    if ( g_topic[g_at+1] == '/' ) {
      while ( g_topic[g_at] != '\n' ) {
        g_at++; 
      } // while()
      
      token.data = "\n";
      return ; 
    } // if()
  } // if()
  
  if ( g_topic[g_at] >= 48 && g_topic[g_at] <= 57 ) { 
    Math_take( token, temp, next_temp ) ;

    token.type = "count" ;  
  } // if()
  
  else if ( g_topic[g_at] == '.' ) { 
    if ( g_topic[g_at+1] >= 48 && g_topic[g_at+1] <= 57 ) {
      g_at++; // 讀到小數點後第一個數字 
      Dot_first( token, temp, next_temp ) ;
    } // if()
    else {
      temp = '\0' ; 
    } // else()
  } // else if()

  
  // 符號+-*/
  else if ( g_topic[g_at] == '*' || g_topic[g_at] == '/' || g_topic[g_at] == '+' || g_topic[g_at] == '-' ) {
    token.data = token.data + g_topic[g_at] ; 
    if ( g_topic[g_at] == '*' || g_topic[g_at] == '/' )
      token.type = "term" ; 
    else if ( g_topic[g_at] == '+' || g_topic[g_at] == '-' ) 
      token.type = "sign" ; 
  } // else if()
  
  // 英文 
  else if ( ( g_topic[g_at] >= 65 && g_topic[g_at] <= 90 ) ||
            ( g_topic[g_at] >= 97 && g_topic[g_at] <= 122 ) ) {
    English_start( token, temp, next_temp ) ; 
    token.type = "IDENT" ; 
  } // else if()
  
  // boolean  '=' | '<>' | '>' | '<' | '>=' | '<='
  else if ( g_topic[g_at] == '=' || g_topic[g_at] == '<' || g_topic[g_at] == '>' ) { 
    token.data = token.data + g_topic[g_at] ; 
    token.type = "boolean" ; 
    
    if ( g_topic[g_at] == '>' || g_topic[g_at] == '<' ) {
      
      if ( g_topic[g_at] == '<' && g_topic[g_at+1] == '>' ) 
        token.data = "<>" ;
      else if ( g_topic[g_at] == '>' && g_topic[g_at+1] == '=' ) 
        token.data = ">=" ; 
      else if ( g_topic[g_at] == '<' && g_topic[g_at+1] == '=' )
        token.data = "<=" ;
      
      if ( token.data.size() > 1 )  g_at++ ;  
    } // if()
  } // else if() 
  // statement :=
  else if ( g_topic[g_at] == ':' ) { 
    
    if ( g_topic[g_at+1] == '=' ) { 
      token.data = ":=" ; 
      token.type = "statement" ; 
      g_at++;
    } // if()
  } // else if() 
  // ; 
  else if ( g_topic[g_at] == ';' ) {
    token.data = ";" ; 
    token.type = "statement" ; 
  } // else if() 
  // ()
  else if ( g_topic[g_at] == ')' ) { 
    token.data = ")" ; 
    token.type = "bracket_right" ; 
    next_temp = '\0';
  } // else if() 
  else if ( g_topic[g_at] == '(' ) { 
    token.data = "(" ; 
    token.type = "bracket_left" ; 
    next_temp = '\0';
  } // else if() 
  
  else if ( g_topic[g_at] == '\n' ) {
    token.data = "\n" ; 
    token.type = "next_line" ; 
  } // else if()
  else {
    
    if ( g_error_1 == false ) g_error_char = g_topic[g_at] ; 
    token.data = g_topic[g_at] ; 
    token.type = "not_define" ; 
    g_error_1 = true; 
    
  } // else() 
  
  return;
} // Get_token()


// --------------------scanner start-----------------------
bool Check_defined( int now ) {
  for ( int i = 0 ; i < g_id_count.size() && g_id_count.size() != 0  ; i++ ) {
    if ( g_scan.at( now ).data == g_id_count.at( i ).id ) 
      return false ;            
  } // for
  
  return true ; // 尚未定義 
} // Check_defined()




void Get_next_line_token() {
   
  while ( g_scan.at( g_th ).data != "\n" && g_th < g_scan.size()-1 ) {
    // cout << g_th << endl   ; 
    g_th++;
  } // while()
  
  /*
  while ( g_scan.at( g_th ).data == "\n" && g_th < g_scan.size()-1 ) {
    // cout << g_th << endl   ; 
    g_th++;
  } // while()
  */
  
} // Get_next_line_token()

void Get_next_token() { 
  if ( g_first_token == false ) g_first_token = true ; 
  else g_th++ ;
  
  if ( g_scan.at( g_th ).type == "not_defined" ) { 
    g_error_1 = true ; 
    g_error_2 = true ; 
    return ; 
  } // if()
   
  while ( g_scan.at( g_th ).data == "\n" && g_th < g_scan.size()-1 ) {
    // cout << g_th << endl   ; 
    g_th++;
    if ( g_scan.at( g_th ).type == "not_defined" ) {
      g_error_1 = true ; 
      g_error_2 = true ; 
      return ; 
    } // if()
  } // while()
} // Get_next_token()

void If_next() { 
  if ( g_scan.at( g_th ).data == "\n" ) 
    Get_next_token() ; 
} // If_next()


void Command() { 
  int og = 0 ; 
  // cout << "Command :" << g_scan.at(g_th).data << endl ; 
  If_next();
  if ( g_scan.at( g_th ).data == "quit" ) {
    g_quit = true ;
    return ; 
  } // if()
  else if ( g_scan.at( g_th ).type == "IDENT" ) {
    og = g_th ; 
    g_th++ ; 
    If_next();
    // cout << "Command :" << g_scan.at(g_th).data << endl ;
    if ( g_scan.at( g_th ).data == ":=" ) {
      g_type = 1 ; 
      g_th++;
      If_next();
      ArithExp();
    } // if()
    else {
      if ( g_scan.at( g_th ).type == "IDENT" ) {
        g_error_2 = true ; 
        return ; 
      } // if()
      
      if ( Check_defined( og ) == true ) { // 尚未定義 失敗跳回 
        g_th = og ; 
        g_error_2 = true;  
        g_error_3 = true ; 
        return ;        
      } // if()
      
      IDlessArithExpOrBexp();
    } // else()
  } // if()
  else { 
    NOT_ID_StartArithExpOrBexp() ;  
  } // else() 
  
  if ( g_error_2 == true ) return ; 
  
  if ( g_scan.at( g_th ).data != ";"  ) 
    g_error_2 = true;
  // if ( g_scan.at(g_th).data == ";" ) 
  //  g_th++;
    
    

} // Command()

void IDlessArithExpOrBexp() { 
  // cout << "IDlessArithExpOrBexp :" << g_scan.at(g_th).data << endl ; 
  if ( g_scan.at( g_th ).type == "term" || g_scan.at( g_th ).type == "sign" ) {
    while ( g_scan.at( g_th ).type == "term" || g_scan.at( g_th ).type == "sign" ) { //  +.-.*./
      if ( g_scan.at( g_th ).data == "+" || g_scan.at( g_th ).data == "-" ) {
        g_th++;
        If_next();
        Term();
      } // if()
      else if ( g_scan.at( g_th ).data == "*" || g_scan.at( g_th ).data == "/" ) {
        g_th++;
        If_next();
        Factor();
      } // else if()
      
      if ( g_error_2 == true ) return ; 
    } // while()
  } // if()
  
  if ( g_scan.at( g_th ).type == "boolean" ) {
    BooleanOprator();
    if ( g_error_2 == true ) return ;
    ArithExp();
    if ( g_error_2 == true ) return ;
  } // if()
  
} // IDlessArithExpOrBexp()

void BooleanOprator() { 

  // cout << "BooleanOprator :" << g_scan.at(g_th).data << endl ; 
  g_type = 2 ; 
  if ( g_scan.at( g_th ).type != "boolean" ) g_error_2 = true ;  // 非BOOLEAN 文法錯誤 
  g_th++; // >.< 的下一個 
  If_next();
} // BooleanOprator()
     
void NOT_ID_StartArithExpOrBexp() { 
  // cout << "NOT_ID_StartArithExpOrBexp :" << g_scan.at(g_th).data << endl ; 
  NOT_ID_StartArithExp();
  
  if ( g_scan.at( g_th ).type == "boolean" ) {
    BooleanOprator();
    ArithExp();
  } // if()
  
} // NOT_ID_StartArithExpOrBexp()

void NOT_ID_StartArithExp() { 
  // cout << "NOT_ID_StartArithExp :" << g_scan.at(g_th).data << endl ; 
  NOT_ID_StartTerm();
  while ( g_scan.at( g_th ).data == "+" || g_scan.at( g_th ).data == "-" ) {  
    g_th++; // 目 前位置在數字 
    If_next();
    Term() ; 
  } // while()
} // NOT_ID_StartArithExp()

void NOT_ID_StartTerm() { 
  // cout << "NOT_ID_StartTerm :" << g_scan.at(g_th).data << endl ; 
  NOT_ID_StartFactor();
  while ( g_scan.at( g_th ).data == "*" || g_scan.at( g_th ).data == "/" ) { 
    g_th++; // 目前位置在數字 
    If_next();
    Factor(); 
  } // while()
} // NOT_ID_StartTerm()

void NOT_ID_StartFactor() { 
  // cout << "NOT_ID_StartFactor : " << g_scan.at(g_th).data << g_scan.at(g_th).type<< endl ; 
  if ( g_scan.at( g_th ).data == "+" || g_scan.at( g_th ).data == "-" 
       || g_scan.at( g_th ).type == "count" ) { // [ SIGN ] NUM
    if ( g_scan.at( g_th ).data == "+" && g_scan.at( g_th+1 ).type == "count" ) {
      g_th++; // 測到為sign 取得數字 
      If_next();
    } // if()
    else if ( g_scan.at( g_th ).data == "-" && g_scan.at( g_th+1 ).type == "count" ) {
      g_th++; // 測到為sign 取得數字 
      If_next();
    } // else if()
    else { 
    } // else()
    
    g_th++;
    If_next();
  } // if()
  else if ( g_scan.at( g_th ).type == "bracket_left" ) {
    g_th++;
    If_next();
    ArithExp();
    if ( g_scan.at( g_th ).type == "bracket_right" ) { // 回來後要左括號 
      if ( g_scan.at( g_th-1 ).type == "bracket_left" ) {
        g_error_2 = true ;
        return;
      } // if()
      
      g_th++; 
      If_next();
    } // if()
  } // else if()
  else { // 文法錯誤  
    g_error_2 = true ; 
    // cout << "我錯啦" << endl; 
    // cout << g_scan.at(g_th).data << endl ;
    // cout << g_scan.at(g_th).type  << endl ; 
    return ; 
  } // else()
  
} // NOT_ID_StartFactor()

void ArithExp() { 

  // cout << "ArithExp :" << g_scan.at(g_th).data << endl ; 

  Term(); 
  if ( g_error_2 == true ) {
    // cout << "這裡有問題" ;
    return ;
  } // if()
  
  while ( g_scan.at( g_th ).data == "+" || g_scan.at( g_th ).data == "-" ) { 
    g_th++;
    If_next();
    Term() ; 
    if ( g_error_2 == true ) return ; 
  } // while
  
} // ArithExp() 
  
void Term() { 
  // cout << "term :" << g_scan.at(g_th).data << endl ; 
  
  Factor(); 
  if ( g_error_2 == true ) return ; 
  while ( g_scan.at( g_th ).data == "*" || g_scan.at( g_th ).data == "/" ) { 
    g_th++;
    If_next();
    Factor() ; 
    if ( g_error_2 == true ) return ; 
  } // while()
  
} // Term()
              
void Factor() { 
  
  // cout << "factor :" << g_scan.at(g_th).data << endl ;  
  if ( g_scan.at( g_th ).type == "IDENT" ) {
    if ( Check_defined( g_th ) == true ) {
      g_error_2 = true ; 
      g_error_3 = true ; 
      return ; 
    } // if()
    
    g_th++;
    If_next();
  } // if()
  else if ( g_scan.at( g_th ).data == "+" || ( g_scan.at( g_th ).data == "-" ) ) {
    g_th++; 
    If_next();
    if ( g_scan.at( g_th ).type == "count" || g_scan.at( g_th ).type == "IDENT" ) {
      g_th++;
      If_next();
    }  // if()
    // else cout << "factor_error" ;  
    
  } // else if()
  else if ( g_scan.at( g_th ).type == "count" ) {
    g_th++;
    If_next();
  } // else if()
  else if ( g_scan.at( g_th ).type == "bracket_left" ) {
    g_th++;
    If_next();
    ArithExp();
    
    if ( g_scan.at( g_th ).type == "bracket_right" ) { // 回來後要右括號 
      if ( g_scan.at( g_th-1 ).type == "bracket_left" ) {
        g_error_2 = true ;
        return;
      } // if
      
      g_th++; 
      If_next(); 
    } // if
  } // else if 
  else { // 文法錯誤  
    g_error_2 = true ;     
  } // else
} // Factor()          

void Scanner() { 
  Command(); 
} // Scanner()

void Cut_scan( int start, int end ) {
  for ( int i = start; i < end ; i++ ) {
    if ( g_scan.at( i ).data != "\n" && g_scan.at( i ).data != ";" ) 
      g_calcu_v.push_back( g_scan.at( i ) );
  } // for()
} // Cut_scan()

void Calcu() {
  bool already = false ;  
  bool find = false ; 
  Token_data cal ; 
  string all_count = "" ;
  string type1_id = "" ;
  string before = "" ; 
  string after = "" ; 
  string all = "" ;  
  Id_Count temp_id_count ;  
  // int type = 3;  // 預設為純加減 
  int addr = 0 ; 
  
  for ( int i = 0 ; i < g_calcu_v.size() && already == false ; i++ ) {     // 進行分類 
    if ( g_calcu_v.at( i ).data == ":=" ) g_type = 1, addr = i, already = true ; 
    else if ( g_calcu_v.at( i ).type == "boolean" ) g_type = 2, addr = i, already = true ;
  } // for
  // cout << "type:" << type << endl; 
  
  if ( g_type == 1 ) {
    for ( int i = 0 ; i < addr ; i++ ) {  // 等號前半部 
      if ( g_calcu_v.at( i ).data != "\n" ) 
        type1_id = type1_id + g_calcu_v.at( i ).data; 
    } // for 
    
    Change( 2 ); // id_to_count
    
    for ( int i = addr + 1 ; i < g_calcu_v.size() ; i++ ) { // 等 號後半部 -1是因為去掉";" 
      all_count = all_count + g_calcu_v.at( i ).data; 
      cal.data = g_calcu_v.at( i ).data ; 
      g_alg.push_back( cal ) ; 
    } // for 
    
    g_final = ArithExp2() ; 
    Double_to_string( all_count, g_final );
    g_alg.clear();
    Update( type1_id, all_count, find ) ; 
     
    if ( g_type == 1 && find == false ) { // 若 是狀況1且沒找到 登陸記事本 
      temp_id_count.id = g_calcu_v.at( 0 ).data; 
      temp_id_count.count = all_count;
      g_id_count.push_back( temp_id_count ) ; 
      // cout <<temp_id_count.id << " " << temp_id_count.count << "我登陸了"<< endl ;
    } // if
    
    // cout << "/////"  << "/////" << g_calcu_v.size() << endl;
    cout << "> " << all_count << endl ;
    
  } // if()
  else if ( g_type == 2 ) {
    Change( 0 ) ; // find 用不到
    
    for ( int i = 0 ; i < addr ; i++ ) {  // 等號前半部 
      // before = before + g_calcu_v.at(i).data ; 
      cal.data = g_calcu_v.at( i ).data ; 
      g_alg.push_back( cal ) ; 
    } // for 

    g_final = ArithExp2() ;  
    Double_to_string( before, g_final );
    g_alg.clear();
    g = 0 ;
    for ( int i = addr + 1 ; i < g_calcu_v.size() ; i++ ) { // 等號後半部 
      
      cal.data = g_calcu_v.at( i ).data ; 
      g_alg.push_back( cal ) ; 
    } // for 

    g_final = ArithExp2() ;  
    Double_to_string( after, g_final );
    g_alg.clear();
    
    if ( Deal_boolean( before, g_calcu_v.at( addr ).data, after ) == true ) 
      cout << "> " << "true" << endl ; 
    else 
      cout << "> " << "false" << endl ; 
    
    // cout << "> " << before << g_calcu_v.at(addr).data << after << endl ; 
  
  } // else if() 
  else if ( g_type == 3 ) {
    
    Change( 0 ) ;
    for ( int i = 0 ; i < g_calcu_v.size() ; i++ ) { // 等號後半部 
      cal.data = g_calcu_v.at( i ).data ; 
      g_alg.push_back( cal ) ; 
    } // for()
    // cout << "/////" << all << "/////" << g_calcu_v.size() << endl;
    g_final = ArithExp2() ;  
    Double_to_string( all, g_final );
    g_alg.clear();
    
    cout << "> " << all << endl ; 
  
  } // else if() 
} // Calcu()

int main() { 
  char temp ; // 讀取1個字元
  char next_temp ; 
  int start = 0 ; 
  int end = 0 ; 
  string func ; 
  bool unrecognize ;  
  bool at_next = true ; 
  char title ; 
  
  cout << "Program starts..." << endl ;
  
  while ( title != '\n' ) 
    title = getchar(); // 讀換行 
  
  Token_data token  ;
  
  
  int i = 0 ; 
  
  while ( scanf( "%c", &g_topic[i] ) == 1 ) { // 全部元件讀進topic  
    // if ( g_topic[i] != ' ' ) 
    i++;
  } // while

  /*
  for ( int k = 0 ;  g_topic[k] != '\0' ; k ++ ) {    // 印出做確認 
    if ( g_topic[k] != '\n')
      cout << g_topic[k] << " " << k << endl  ;
    else 
      cout << "N-LINE" << " " << k << endl  ; 
  }
  */
  
  // 將全部元件做成token in vector_scan 
  for ( int i = 0 ; i < 1000 && g_topic[g_at] != '\0' && g_at < 5000 ; i++ ) {            
    Get_token( token, temp, next_temp, at_next ) ;
    
    if ( token.data != "\0" && token.data != " " && g_error_1 == false )  
      g_scan.push_back( token ) ; 
      
    if ( g_error_1 == true ) {
      while (  g_topic[g_at] != '\n' && g_at < sizeof( g_topic ) - 1  ) { // get 到未定義時整行讀掉 
        g_at++; 
      } // while
    } // if 
    
    if ( g_error_char != EOF && g_error_char != '\0' && g_error_char != ' '  && g_error_1 == true ) {
      token.type = "not_defined";
      g_scan.push_back( token ) ; 
      // cout << "Unrecognized token with first char : '" << g_error_char << "'"<<  endl  ;
    } // if
    
    g_error_1 = false; 
    
    token.data = "" ; 
    token.type = "" ;
  } // for()
  
  // for ( int i = 0 ; i < g_scan.size() - 1 ; i ++ ) 
  //  cout << i << g_scan.at(i).data << endl ;  
  
  while ( g_th < g_scan.size() - 1 && g_quit == false ) {

    // if ( g_error_2 == false ) 
    Get_next_token();
    g_error_1 = false ;   
    g_error_2 = false ;
    g_error_3 = false ; 
    
    if ( g_scan.at( g_th ).data != " " && g_scan.at( g_th ).data != "\n"  )  {
      start = g_th ; 
      Scanner() ; 
      end = g_th ; 
    } // if()
     
    if ( g_quit == false ) {
      if ( g_error_1 != true && g_error_2 != true && g_error_3 != true ) Cut_scan( start, end ); 
      // cout << "***" ; 
      for ( int i = 0 ; i < g_calcu_v.size()  ; i ++ ) {
        
        // cout << g_calcu_v.at(i).data ;
         
      } // for()
      // cout << "***" << endl ; 
      if ( g_error_1 == false && g_error_2 == true && g_error_3 == false 
           && g_scan.at( g_th ).data != "\n" && g_scan.at( g_th ).type != "not_defined" ) 
        cout << "> " << "Unexpected token : '" << g_scan.at( g_th ).data << "'" << endl ;
        
      if ( g_error_2 == true && g_error_3 == false 
           && g_scan.at( g_th ).data != "\n" && g_scan.at( g_th ).type == "not_defined" 
           && g_quit == false  ) 
        cout << "> " << "Unrecognized token with first char : '" << g_scan.at( g_th ).data << "'" << endl;
        
      if ( g_error_3 == true ) 
        cout << "> " << "Undefined identifier : '" << g_scan.at( g_th ).data << "'" << endl; 
      
      if ( g_scan.at( g_th ).type != "not_defined" ) Get_next_line_token() ; 
      // if ( g_scan.at( g_th ).type == "not_defined" ) g_th++ ; 
      
      if ( g_error_1 == false && g_error_2 == false && g_error_3 == false ) Calcu() ;
      
      // for ( int i = 0 ; i < g_id_count.size() ; i++ ) 
      //  cout << g_id_count.at(i).id  << " " << g_id_count.at(i).count << endl ;  
      
      g_type = 3 ; 
      g_calcu_v.clear();
      g_alg.clear();
      g_final = 0 ; 
      g = 0;
      // cout << "--------------------------------------------" << endl ; 
    } // if ( g_quit == false )
  } // while()
  
  cout << "> Program exits..." ; 
  
  
  
} // main()
