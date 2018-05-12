(function () {


    Handlebars.registerHelper('bo', function (row) {
        console.log(row)

        if (row === 'r') {
            return ' red ';
        }else if(row==='b'){
            return ' blue';
            
        }else if(row==='g'){
            return ' green';
            
        }
        

    });


    var source = document.querySelector('.content');
    var templateString =`
    
    <h1>{{year}}</h1>
        <table>
            <thead>
                <tr>
                    <td>期数</td>
                    <th colspan="6">平码</th>
                    <td>特码</td>
                </tr>
            </thead>
            <tbody>
                {{#each terms}}
                <tr>
                    <td>{{period}}</td>
                    {{#each prizes}}
                    <td>
                        <div class="number"> <div class="nb {{bo color}}">{{number}}</div> 
                        
                        <div class="sx">{{sx}}</div>
                        </div>
                   
                    
                    </td>
                    {{/each}}

                    
                  <td class="yellow">
                  {{#with luck}}
                  <div class="number"> <div class="nb {{bo color}}">{{number}}</div> 
                  <div class="sx">{{sx}}</div>
                  
                  </div>
                
                  {{/with}}
                    
                  </td>
                   
                </tr>
                {{/each}}
            </tbody>
        </table>
    `;


    var template = Handlebars.compile(templateString);
    var html = template({
        year: window.dataset['year'],
        terms: window.dataset["terms"]
    });


    source.innerHTML = html;


    console.log(template, source);

 
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