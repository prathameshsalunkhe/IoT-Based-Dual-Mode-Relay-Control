$(".btn").click(function(){
  
      var ipAddress =$(".ip").val() ;
      var message=$(".message").val();
      var mode=$(".mode").val();
        var url = "http://" + ipAddress + "/" + message+mode;
        var xhttp = new XMLHttpRequest();
        xhttp.open("GET", url, true);
        xhttp.send();
        console.log(url);
});