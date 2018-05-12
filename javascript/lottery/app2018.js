(function () {


    var source = document.querySelector('.content');
    
 
   document.getElementById('generate').addEventListener('click',function(){
    domtoimage.toJpeg(source, { quality: 0.95 })
    .then(function (dataUrl) {
        // var link = document.createElement('a');
        // link.download = 'my-image-name.jpeg';
        // link.href = dataUrl;
        // link.click();

        var img = new Image();
        img.src = dataUrl;
        document.body.appendChild(img);

    });
   })
})();