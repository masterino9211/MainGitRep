$(document).ready(function(){
    
    $("#tardis").toggle();
      speed=18;step=1;
     shakeIt1("#create");
     setTimeout(function() {
      shakeIt2("#login");
}, 4800); 
      
     setTimeout(function(){
         var appear=0;
         $("#tardis").prepend("<embed name='tardis' src='sounds/tardis12.mp3' loop='true' hidden='true' autostart='true'></embed>");
             var mat= window.setInterval(function(){
           
            $("#tardis").fadeToggle(1500);
            appear++;
            if(appear==9) {
                $("#tardis").fadeIn(1200);
                clearInterval(mat);}
        },300);
     },1);

});
function shakeIt1(element){ // z=250 // t=140
    var x=0;
    var y=0;
    window.setInterval(function(){
          
          if(x<250 && y==0)
            {
              x+=step;
              $(element).css("left",x+"px");
               
            }
         if(x==250 && y<140)
             {
              y+=step;
              $(element).css("top",y+"px");
               
            }
         if(x>0 && y==140)
             {
              x-=step;
              $(element).css("left",x+"px");
               
            }   
          if(x==0 && y>0)
             {
              y-=step;
              $(element).css("top",y+"px");
               
            } 
    
  },speed);
}
function shakeIt2(element){
    var x=0;
    var y=0;
    window.setInterval(function(){
          if(x==0 && y>-120)
             {
              y-=step;
              $(element).css("top",y+"px");
               
            } 
          if(x<250 && y==-120)
            {
              x+=step;
              $(element).css("left",x+"px");
               
            }
         if(x==250 && y<20)
             {
              y+=step;
              $(element).css("top",y+"px");
               
            }
         if(x>0 && y==20)
             {
              x-=step;
              $(element).css("left",x+"px");
               
            }   
          
    
  },speed);
}



