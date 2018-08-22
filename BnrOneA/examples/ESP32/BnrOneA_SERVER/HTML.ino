String get_index()
{
  String HTML_CODE = "\
        <html>\
          <head>\
            <title>BnrOneA ESP32 Menu</title>\
            <meta charset='utf-8'>\
            <meta name='viewport' content='width=device-width, initial-scale=1'>\
            <link rel='stylesheet' href='https://maxcdn.bootstrapcdn.com/bootstrap/4.1.3/css/bootstrap.min.css'>\
            <script src='https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js'></script>\
            <script src='https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.3/umd/popper.min.js'></script>\
            <script src='https://maxcdn.bootstrapcdn.com/bootstrap/4.1.3/js/bootstrap.min.js'></script>\
          </head>\
          <script>\
          $(document).ready(function() { });\
          </script>\
          <body>\
          <div class='container'>\
              <h3 class='col-md-12' style='text-align:center;'>Welcome to BnrOneA ESP32 WebPage Menu</h3>\
              <img src='http://botnroll.com/onea/img/One_A.jpg' class='responsive offset-md-4 col-md-4'></img><br>\
              <div class='row justify-content-md-center'>\
              <a id='button_lcd' href='lcd' role='button' class='btn btn-primary col-md-4'>LCD Control</a>\
              <a id='button_joy' href='joy' role='button' class='btn btn-primary col-md-4'>JoyStick Control</a>\
              <div>\
          </div>\
          </body>\
      </html>";
  
  return HTML_CODE;
}

String get_joystick_page()
{
  String HTML_CODE = "\
        <html>\
          <head>\
            <title>BnrOneA ESP32 JoyStick</title>\
            <meta charset='utf-8'>\
            <meta name='viewport' content='width=device-width, initial-scale=1'>\
            <script src='https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js'></script>\
            <script src='https://cdn.rawgit.com/jeromeetienne/virtualjoystick.js/master/virtualjoystick.js'></script>\
          </head>\
          <script>\
          $(document).ready(function() {\
              var joystick  = new VirtualJoystick({ container : document.getElementById('container'), mouseSupport  : true, });\
              var outputEl  = document.getElementById('result');\
              setInterval(function(){   x = joystick.deltaX(); y = joystick.deltaY();\
                outputEl.innerHTML  = '<b>Result:</b> dx:'+x + ' dy:'+y;\
              $.get( 'cntrl', { x:x , y:y}).done(function( data ) {}); }, 33.3);\
          });\
          </script>\
          <body>\
          <div class='container'>\
            <h4>Welcome to BnrOneA ESP32 Joystick Control</h4>\
            <p>Touch the screen</p> \
            <span id='result'></span>\
          </div>\
          </body>\
      </html>";
  
  return HTML_CODE;
}

String get_lcd_page()
{
  String HTML_CODE = "\
        <html>\
          <head>\
            <title>BnrOneA ESP32 LCD</title>\
            <meta charset='utf-8'>\
            <link rel= 'shortcut icon' href= 'https://www.botnroll.com/img/favicon.jpg '>\
            <meta name='viewport' content='width=device-width, initial-scale=1'>\
            <link rel='stylesheet' href='https://maxcdn.bootstrapcdn.com/bootstrap/4.1.3/css/bootstrap.min.css'>\
            <script src='https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js'></script>\
            <script src='https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.3/umd/popper.min.js'></script>\
            <script src='https://maxcdn.bootstrapcdn.com/bootstrap/4.1.3/js/bootstrap.min.js'></script>\
          </head>\
          <script>\
          $(document).ready(function() {\
              $( '#send_lcd').click(function(){\
                    var txt1 = document.getElementById('line1').value;\
                    var txt2 = document.getElementById('line2').value;\
                    $.get( 'lcd_control', { line1:txt1 , line2:txt2}).done(function( data ) {});\
              });\
          });\
          </script>\
          <body>\
          <div class='container'>\
              <h3 class='col-md-12' style='text-align:center;'>Welcome to BnrOneA ESP32 LCD Control</h3>\
              <div class= 'row justify-content-md-center'>\
              <input id='line1' class='col-md-12' placeholder= 'LCD Line 1' style= 'text-align:center;margin-top:10px; '></input>\
              <input id='line2' class='col-md-12' placeholder= 'LCD Line 2' style= 'text-align:center;margin-top:10px; '></input>\
              <a id='send_lcd' role= 'button ' class='btn btn-primary col-md-12' style= 'color:white;margin-top:10px; '>SEND</a>\
              <div>\
          </div>\
          </body>\
      </html>";
  
  return HTML_CODE;
}
