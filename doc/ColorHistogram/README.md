# 利用图像原始全局直方图进行相似性判别

## 同一幅图像，不同分辨率情况下相似度检验 

-  图片SardiniaHawkMoth_ZH-CN3672906054  

|图片名|分辨率1|分辨率2|相似性检验结果|
|:-:|:-:|:-:|:-:|
|SardiniaHawkMoth_ZH-CN3672906054|	800x480|	1920x1080	|0.958796|
|SardiniaHawkMoth_ZH-CN3672906054|	800x480|	1366x768	|0.953578|
|SardiniaHawkMoth_ZH-CN3672906054|	800x480|	1280x768	|0.961696|
|SardiniaHawkMoth_ZH-CN3672906054|	800x480|	1024x768	|0.979306|
|SardiniaHawkMoth_ZH-CN3672906054|	800x480|	800x600	    |0.976014|
|SardiniaHawkMoth_ZH-CN3672906054|	800x480|	800x480	    |1       |
|SardiniaHawkMoth_ZH-CN3672906054|	800x480|	768x1280	|0.891631|
|SardiniaHawkMoth_ZH-CN3672906054|	800x480|	720x1280	|0.881007|
|SardiniaHawkMoth_ZH-CN3672906054|	800x480|	640x480	    |0.977892|
|SardiniaHawkMoth_ZH-CN3672906054|	800x480|	480x800	    |0.907006|
|SardiniaHawkMoth_ZH-CN3672906054|	800x480|	400x240	    |0.997263|
|SardiniaHawkMoth_ZH-CN3672906054|	800x480|	320x240	    |0.972381|

<center class="SardiniaHawkMoth_ZH-CN3672906054">
    <img src="images/SardiniaHawkMoth_ZH-CN3672906054/SardiniaHawkMoth_ZH-CN3672906054_800x480_base.jpg" width="400" height='300'/><img src="images/SardiniaHawkMoth_ZH-CN3672906054/SardiniaHawkMoth_ZH-CN3672906054_1920x1080_test.jpg" width="400" height='300'/><img src="images/SardiniaHawkMoth_ZH-CN3672906054/SardiniaHawkMoth_ZH-CN3672906054_1366x768_test.jpg" width="400" height='300'/><img src="images/SardiniaHawkMoth_ZH-CN3672906054/SardiniaHawkMoth_ZH-CN3672906054_1280x768_test.jpg" width="400" height='300'/><img src="images/SardiniaHawkMoth_ZH-CN3672906054/SardiniaHawkMoth_ZH-CN3672906054_1024x768_test.jpg" width="400" height='300'/><img src="images/SardiniaHawkMoth_ZH-CN3672906054/SardiniaHawkMoth_ZH-CN3672906054_800x600_test.jpg" width="400" height='300'/><img src="images/SardiniaHawkMoth_ZH-CN3672906054/SardiniaHawkMoth_ZH-CN3672906054_800x480_test.jpg" width="400" height='300'/><img src="images/SardiniaHawkMoth_ZH-CN3672906054/SardiniaHawkMoth_ZH-CN3672906054_768x1280_test.jpg" width="400" height='300'/><img src="images/SardiniaHawkMoth_ZH-CN3672906054/SardiniaHawkMoth_ZH-CN3672906054_720x1280_test.jpg" width="400" height='300'/><img src="images/SardiniaHawkMoth_ZH-CN3672906054/SardiniaHawkMoth_ZH-CN3672906054_640x480_test.jpg" width="400" height='300'/><img src="images/SardiniaHawkMoth_ZH-CN3672906054/SardiniaHawkMoth_ZH-CN3672906054_480x800_test.jpg" width="400" height='300'/><img src="images/SardiniaHawkMoth_ZH-CN3672906054/SardiniaHawkMoth_ZH-CN3672906054_400x240_test.jpg" width="400" height='300'/><img src="images/SardiniaHawkMoth_ZH-CN3672906054/SardiniaHawkMoth_ZH-CN3672906054_320x240_test.jpg" width="400" height='300'/>
</center>  
  
  
-  图片Narrenmuehle_ZH-CN5582540867  
  
|图片名|分辨率1|分辨率2|相似性检验结果|
|:-:|:-:|:-:|:-:|
|Narrenmuehle_ZH-CN5582540867|	768x1280|	1920x1080	|0.776527|
|Narrenmuehle_ZH-CN5582540867|	768x1280|	1366x768	|0.720142|
|Narrenmuehle_ZH-CN5582540867|	768x1280|	1280x768	|0.793931|
|Narrenmuehle_ZH-CN5582540867|	768x1280|	1024x768	|0.288264|
|Narrenmuehle_ZH-CN5582540867|	768x1280|	800x600	    |0.469492|
|Narrenmuehle_ZH-CN5582540867|	768x1280|	800x480	    |0.51643 |
|Narrenmuehle_ZH-CN5582540867|	768x1280|	768x1280	|1       |
|Narrenmuehle_ZH-CN5582540867|	768x1280|	720x1280	|0.994265|
|Narrenmuehle_ZH-CN5582540867|	768x1280|	640x480	    |0.505481|
|Narrenmuehle_ZH-CN5582540867|	768x1280|	480x800	    |0.578413|
|Narrenmuehle_ZH-CN5582540867|	768x1280|	400x240	    |0.577864|
|Narrenmuehle_ZH-CN5582540867|	768x1280|	320x240	    |0.595266|
|Narrenmuehle_ZH-CN5582540867|	768x1280|	240x320	    |0.628363|  
  
<center class="Narrenmuehle_ZH-CN5582540867">
    <img src="images/Narrenmuehle_ZH-CN5582540867/Narrenmuehle_ZH-CN5582540867_768x1280_base.jpg" width="400" height='300' alt='基准图'/><img src="images/Narrenmuehle_ZH-CN5582540867/Narrenmuehle_ZH-CN5582540867_1920x1080_test.jpg" width="400" height='300'/><img src="images/Narrenmuehle_ZH-CN5582540867/Narrenmuehle_ZH-CN5582540867_1366x768_test.jpg" width="400" height='300'/><img src="images/Narrenmuehle_ZH-CN5582540867/Narrenmuehle_ZH-CN5582540867_1280x768_test.jpg" width="400" height='300'/><img src="images/Narrenmuehle_ZH-CN5582540867/Narrenmuehle_ZH-CN5582540867_1024x768_test.jpg" width="400" height='300'/><img src="images/Narrenmuehle_ZH-CN5582540867/Narrenmuehle_ZH-CN5582540867_800x600_test.jpg" width="400" height='300'/><img src="images/Narrenmuehle_ZH-CN5582540867/Narrenmuehle_ZH-CN5582540867_800x480_test.jpg" width="400" height='300'/><img src="images/Narrenmuehle_ZH-CN5582540867/Narrenmuehle_ZH-CN5582540867_768x1280_test.jpg" width="400" height='300'/><img src="images/Narrenmuehle_ZH-CN5582540867/Narrenmuehle_ZH-CN5582540867_720x1280_test.jpg" width="400" height='300'/><img src="images/Narrenmuehle_ZH-CN5582540867/Narrenmuehle_ZH-CN5582540867_640x480_test.jpg" width="400" height='300'/><img src="images/Narrenmuehle_ZH-CN5582540867/Narrenmuehle_ZH-CN5582540867_480x800_test.jpg" width="400" height='300'/><img src="images/Narrenmuehle_ZH-CN5582540867/Narrenmuehle_ZH-CN5582540867_400x240_test.jpg" width="400" height='300'/><img src="images/Narrenmuehle_ZH-CN5582540867/Narrenmuehle_ZH-CN5582540867_320x240_test.jpg" width="400" height='300'/><img src="images/Narrenmuehle_ZH-CN5582540867/Narrenmuehle_ZH-CN5582540867_240x320_test.jpg" width="400" height='300'/>
</center>

结论：同一张图片利用图像原始全局直方图进行相似性判别时，当图片色彩变化相对平缓时，对不同分辨率的图片具有较高的准确性；当图片色彩变化相对剧烈时，对不同分辨率的图片相似性检测结果不太准确。

## 图像不同但相似的同分辨率和不同分辨率



## 图像不同且不相似的同分辨率和不同分辨率

