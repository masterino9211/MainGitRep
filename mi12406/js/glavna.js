$(document).ready(function() {
    $("form").toggle();
    $("#shrink").toggle();
    $("#pasch").click(function() {
        $('form').slideToggle('slow');
        $("#pasch").toggle();
        $("#shrink").toggle();
    });
    $("#shrink").click(function() {
        $('form').slideToggle('slow');
        $("#pasch").toggle();
       $("#shrink").toggle();
    });
});
