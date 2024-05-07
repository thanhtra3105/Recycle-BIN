const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <!-- <link rel="stylesheet" href="style.css" /> -->
    <title>"Smart Recycle Bin"</title>
</head>

<body>

    <h1 class="tieude">Hiển thị lượng rác</h1>

    <img src="recyclebin.jpg">


    <div id="type">
        <div id="hinh1">
            <div class="circle1"></div>
            <div id="metal">
                <span> 0 </span> %
            </div>
        </div>

        

        <div class="circle3"></div>
        <div id="plastic">
            <span> 0</span> %
        </div>

        <span id="mt">
            Metal
        </span>
        <span id="plt">
            Other
        </span>
        <span id="boc1"></span>
        
        <span id="boc3"></span>

    </div>




    <style>
        .tieude {
            color: blue;
            text-align: center;
            font-weight: 800;
            font-style: italic;
            border: 1px solid blue;
            border-radius: 20%;
            width: 400px;
            height: 40px;
            margin: auto;
            padding: 10px 0 10px 0;
        }

        body {
            font-family: Arial, sans-serif;

        }

        @keyframes fillCircle {
            0% {
                width: 0%;
            }

            100% {
                width: 100%;
            }
        }




        #metal {
            text-align: center;
            color: green;
            font-size: 25px;
            font-style: inherit;
            font-family: Verdana, Geneva, Tahoma, sans-serif;
            /* margin: 10px 50px 10px 10px; */
            /* khoang cach giua cac khung*/
            padding: 10px 10px 10px 10px;
            /* khoang cach giua khung va ca phan tu o trong*/

            position: absolute;
            left: 424px;
            top: 124px;
            border-radius: 50%;
            width: 80px;
            height: 80px;
            display: flex;
            justify-content: center;
            /* can ngang */
            align-items: center;
            /* can doc */
            border: 1px solid green;
            overflow: hidden;
            background-color: white;
        }

        .circle1 {
            border: 1px solid green;
            width: 150px;
            height: 150px;
            border-radius: 50%;
            background-color: rgb(75, 226, 75);
            clip-path: polygon(0 0, 0 100%, 50% 100%, 50% 0);
            position: absolute;
            top: 100px;
            left: 400px;
        }

        #mt {
            border: 1px solid green;
            position: absolute;
            text-align: center;
            width: 80px;
            height: 30px;
            left: 424px;
            top: 270px;
            font-size: 25px;
            padding: 5px 5px 5px 5px;
            /* margin: 20px 0px 0px 0px; */
            /* top right bot left */
        }


        #progressBar {
            height: 100%;
            background-color: green;
            animation: fillCircle 2s ease-in-out forwards;
        }


        #plastic {
            text-align: center;
            color: red;
            font-size: 25px;
            font-style: inherit;
            font-family: Verdana, Geneva, Tahoma, sans-serif;
            /* margin: 10px 10px 10px 10px; */
            padding: 10px 10px 10px 10px;
            width: 80px;
            height: 80px;
            position: absolute;
            left: 824px;
            top: 124px;
            border-radius: 50%;
            display: flex;
            justify-content: center;
            align-items: center;
            border: 1px solid red;
            background-color: white;
        }

        .circle3 {
            width: 150px;
            height: 150px;
            border-radius: 50%;
            background-color: rgb(240, 59, 35);
            /* clip-path: polygon(0 0, 0 100%, 50% 100%, 50% 0); */
            position: absolute;
            top: 100px;
            left: 800px;
        }

        #plt {
            text-align: center;
            border: 1px solid rgb(241, 18, 18);
            position: absolute;
            width: 80px;
            height: 30px;
            left: 824px;
            top: 270px;
            font-size: 25px;
            padding: 5px 5px 5px 5px;
            /* margin: 20px 0px 0px 310px; */
        }

        #type {
            /* border: 1px solid black; 
    width: 100px;
    height: 100px; */
            position: absolute;
            top: 50px;
        }

        img {
            display: block;
            margin: 10px 0 10px 0;
            padding: 10px 10px 10px 10px;
            width: 160px;
            height: 160px;

            position: absolute;
            left: 590px;
            top: 130px;
        }

        html {

            /* background: url("https://media.gettyimages.com/id/184099943/photo/recycle-concept.jpg?s=612x612&w=gi&k=20&c=ot6KcnssBYKnuYpjHCpDUoqBg1kLpI7WrecDUSihvaA=");
    display: flex; */
            align-items: center;
            justify-content: center;
            overflow: hidden;
            background-repeat: no-repeat;

        }

        #boc1 {
            border: 1px solid green;
            width: 150px;
            height: 150px;
            position: absolute;
            left: 400px;
            top: 99px;
            border-radius: 50%;
        }

        /* #boc2 {
            border: 1px solid yellow;
            width: 150px;
            height: 150px;
            position: absolute;
            left: 600px;
            top: 99px;
            border-radius: 50%;
        } */

        #boc3 {
            border: 1px solid red;
            width: 150px;
            height: 150px;
            position: absolute;
            left: 800px;
            top: 99px;
            border-radius: 50%;
        }
    </style>



    <script>
        setInterval(function () {
            getMetal();
            getOther();
        }, 3000);

        function getMetal() {
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function () {
                if (this.readyState == 4 && this.status == 200) {
                    document.getElementById("metal").innerHTML = this.responseText + "%";
                    let percentage = this.responseText;
                    
                    animateCircle(percentage);
                }
            }
            xhttp.open("GET", "doc_metal", true);
            xhttp.send();
           
            const circleElement = document.querySelector('.circle1');
            function animateCircle(percentage) {
                const clipPathValue = `polygon(0 0, 0 100%, ${percentage}% 100%, ${percentage}% 0)`;
                circleElement.style.clipPath = clipPathValue;

            }

        }

          

        function getOther() {
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function () {
                if (this.readyState == 4 && this.status == 200) {
                    document.getElementById("plastic").innerHTML = this.responseText + "%";
                    let percentage = this.responseText;
                    animateCircle(percentage);
                }
            } 
            xhttp.open("GET", "doc_plastic", true);
            xhttp.send();

            const circleElement = document.querySelector('.circle3');
            
            function animateCircle(percentage) {
                const clipPathValue = `polygon(0 0, 0 100%, ${percentage}% 100%, ${percentage}% 0)`;
                circleElement.style.clipPath = clipPathValue;
            }
            
        }

    </script>



</body>

</html>
)=====";