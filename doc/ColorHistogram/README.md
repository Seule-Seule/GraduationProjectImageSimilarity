# 利用图像原始全局直方图进行相似性判别

## 目录
- [利用图像原始全局直方图进行相似性判别](#利用图像原始全局直方图进行相似性判别)
  - [目录](#目录)
  - [实验代码](#实验代码)
  - [同一幅图像，不同分辨率情况下相似度检验](#同一幅图像不同分辨率情况下相似度检验)
  - [图像不同但相似的同分辨率和不同分辨率](#图像不同但相似的同分辨率和不同分辨率)
  - [图像不同且不相似的同分辨率和不同分辨率](#图像不同且不相似的同分辨率和不同分辨率)

## 实验代码

[@实验代码](../ImageSimilarityExperiment/ColorHistogram.cpp)

## [同一幅图像，不同分辨率情况下相似度检验](1颜色直方图同一图像不同分辨率.csv)

-  图片SardiniaHawkMoth_ZH-CN3672906054  

|编号|图片名|分辨率1|分辨率2|相似性检验结果|
|:-:|:-:|:-:|:-:|:-:|
|1|SardiniaHawkMoth_ZH-CN3672906054|	800x480|	1920x1080	|0.958796|
|2|SardiniaHawkMoth_ZH-CN3672906054|	800x480|	1366x768	|0.953578|
|3|SardiniaHawkMoth_ZH-CN3672906054|	800x480|	1280x768	|0.961696|
|4|SardiniaHawkMoth_ZH-CN3672906054|	800x480|	1024x768	|0.979306|
|5|SardiniaHawkMoth_ZH-CN3672906054|	800x480|	800x600	    |0.976014|
|6|SardiniaHawkMoth_ZH-CN3672906054|	800x480|	800x480	    |1       |
|7|SardiniaHawkMoth_ZH-CN3672906054|	800x480|	768x1280	|0.891631|
|8|SardiniaHawkMoth_ZH-CN3672906054|	800x480|	720x1280	|0.881007|
|9|SardiniaHawkMoth_ZH-CN3672906054|	800x480|	640x480	    |0.977892|
|10|SardiniaHawkMoth_ZH-CN3672906054|	800x480|	480x800	    |0.907006|
|11|SardiniaHawkMoth_ZH-CN3672906054|	800x480|	400x240	    |0.997263|
|12|SardiniaHawkMoth_ZH-CN3672906054|	800x480|	320x240	    |0.972381|

|编号|基准图|测试图|
|:-:|:-:|:-:|
|1|<img src="images/SardiniaHawkMoth_ZH-CN3672906054/SardiniaHawkMoth_ZH-CN3672906054_800x480_base.jpg" width="400" height='300' title="800x480"/>800x480|<img src="images/SardiniaHawkMoth_ZH-CN3672906054/SardiniaHawkMoth_ZH-CN3672906054_1920x1080_test.jpg" width="400" height='300' title="1920x1080"/>1920x1080|
|2|<img src="images/SardiniaHawkMoth_ZH-CN3672906054/SardiniaHawkMoth_ZH-CN3672906054_800x480_base.jpg" width="400" height='300' title="800x480"/>800x480|<img src="images/SardiniaHawkMoth_ZH-CN3672906054/SardiniaHawkMoth_ZH-CN3672906054_1366x768_test.jpg" width="400" height='300' title="1366x768"/>1366x768|
|3|<img src="images/SardiniaHawkMoth_ZH-CN3672906054/SardiniaHawkMoth_ZH-CN3672906054_800x480_base.jpg" width="400" height='300' title="800x480"/>800x480|<img src="images/SardiniaHawkMoth_ZH-CN3672906054/SardiniaHawkMoth_ZH-CN3672906054_1280x768_test.jpg" width="400" height='300' title="1280x768"/>1280x768|
|4|<img src="images/SardiniaHawkMoth_ZH-CN3672906054/SardiniaHawkMoth_ZH-CN3672906054_800x480_base.jpg" width="400" height='300' title="800x480"/>800x480|<img src="images/SardiniaHawkMoth_ZH-CN3672906054/SardiniaHawkMoth_ZH-CN3672906054_1024x768_test.jpg" width="400" height='300' title="1024x768"/>1024x768|
|5|<img src="images/SardiniaHawkMoth_ZH-CN3672906054/SardiniaHawkMoth_ZH-CN3672906054_800x480_base.jpg" width="400" height='300' title="800x480"/>800x480|<img src="images/SardiniaHawkMoth_ZH-CN3672906054/SardiniaHawkMoth_ZH-CN3672906054_800x600_test.jpg" width="400" height='300' title="800x600"/>800x600|
|6|<img src="images/SardiniaHawkMoth_ZH-CN3672906054/SardiniaHawkMoth_ZH-CN3672906054_800x480_base.jpg" width="400" height='300' title="800x480"/>800x480|<img src="images/SardiniaHawkMoth_ZH-CN3672906054/SardiniaHawkMoth_ZH-CN3672906054_800x480_test.jpg" width="400" height='300' title='800x480'/>800x480|
|7|<img src="images/SardiniaHawkMoth_ZH-CN3672906054/SardiniaHawkMoth_ZH-CN3672906054_800x480_base.jpg" width="400" height='300' title="800x480"/>800x480|<img src="images/SardiniaHawkMoth_ZH-CN3672906054/SardiniaHawkMoth_ZH-CN3672906054_768x1280_test.jpg" width="400" height='300' title='768x1280'/>768x1280|
|8|<img src="images/SardiniaHawkMoth_ZH-CN3672906054/SardiniaHawkMoth_ZH-CN3672906054_800x480_base.jpg" width="400" height='300' title="800x480"/>800x480|<img src="images/SardiniaHawkMoth_ZH-CN3672906054/SardiniaHawkMoth_ZH-CN3672906054_720x1280_test.jpg" width="400" height='300' title='720x1280'/>720x1280|
|9|<img src="images/SardiniaHawkMoth_ZH-CN3672906054/SardiniaHawkMoth_ZH-CN3672906054_800x480_base.jpg" width="400" height='300' title="800x480"/>800x480|<img src="images/SardiniaHawkMoth_ZH-CN3672906054/SardiniaHawkMoth_ZH-CN3672906054_640x480_test.jpg" width="400" height='300' title='640x480'/>640x480|
|10|<img src="images/SardiniaHawkMoth_ZH-CN3672906054/SardiniaHawkMoth_ZH-CN3672906054_800x480_base.jpg" width="400" height='300' title="800x480"/>800x480|<img src="images/SardiniaHawkMoth_ZH-CN3672906054/SardiniaHawkMoth_ZH-CN3672906054_480x800_test.jpg" width="400" height='300' title='480x800'/>480x800|
|11|<img src="images/SardiniaHawkMoth_ZH-CN3672906054/SardiniaHawkMoth_ZH-CN3672906054_800x480_base.jpg" width="400" height='300' title="800x480"/>800x480|<img src="images/SardiniaHawkMoth_ZH-CN3672906054/SardiniaHawkMoth_ZH-CN3672906054_400x240_test.jpg" width="400" height='300' title='400x240'/>400x240|
|12|<img src="images/SardiniaHawkMoth_ZH-CN3672906054/SardiniaHawkMoth_ZH-CN3672906054_800x480_base.jpg" width="400" height='300' title="800x480"/>800x480|<img src="images/SardiniaHawkMoth_ZH-CN3672906054/SardiniaHawkMoth_ZH-CN3672906054_320x240_test.jpg" width="400" height='300'  title='320x240'/>320x240|
  
  
-  图片Narrenmuehle_ZH-CN5582540867  
  
|编号|图片名|分辨率1|分辨率2|相似性检验结果|
|:-:|:-:|:-:|:-:|:-:|
|1|Narrenmuehle_ZH-CN5582540867|	768x1280|	1920x1080	|0.776527|
|2|Narrenmuehle_ZH-CN5582540867|	768x1280|	1366x768	|0.720142|
|3|Narrenmuehle_ZH-CN5582540867|	768x1280|	1280x768	|0.793931|
|4|Narrenmuehle_ZH-CN5582540867|	768x1280|	1024x768	|0.288264|
|5|Narrenmuehle_ZH-CN5582540867|	768x1280|	800x600	    |0.469492|
|6|Narrenmuehle_ZH-CN5582540867|	768x1280|	800x480	    |0.51643 |
|7|Narrenmuehle_ZH-CN5582540867|	768x1280|	768x1280	|1       |
|8|Narrenmuehle_ZH-CN5582540867|	768x1280|	720x1280	|0.994265|
|9|Narrenmuehle_ZH-CN5582540867|	768x1280|	640x480	    |0.505481|
|10|Narrenmuehle_ZH-CN5582540867|	768x1280|	480x800	    |0.578413|
|11|Narrenmuehle_ZH-CN5582540867|	768x1280|	400x240	    |0.577864|
|12|Narrenmuehle_ZH-CN5582540867|	768x1280|	320x240	    |0.595266|
|13|Narrenmuehle_ZH-CN5582540867|	768x1280|	240x320	    |0.628363|  
  
|编号|基准图|测试图|
|:-:|:-:|:-:|
|1|<img src="images/Narrenmuehle_ZH-CN5582540867/Narrenmuehle_ZH-CN5582540867_768x1280_base.jpg" width="400" height='300' title='768x1280'/>768x1280|<img src="images/Narrenmuehle_ZH-CN5582540867/Narrenmuehle_ZH-CN5582540867_1920x1080_test.jpg" width="400" height='300'  title='1920x1080'/>1920x1080|
|2|<img src="images/Narrenmuehle_ZH-CN5582540867/Narrenmuehle_ZH-CN5582540867_768x1280_base.jpg" width="400" height='300' title='768x1280'/>768x1280|<img src="images/Narrenmuehle_ZH-CN5582540867/Narrenmuehle_ZH-CN5582540867_1366x768_test.jpg" width="400" height='300' title='1366x768'/>1366x768|
|3|<img src="images/Narrenmuehle_ZH-CN5582540867/Narrenmuehle_ZH-CN5582540867_768x1280_base.jpg" width="400" height='300' title='768x1280'/>768x1280|<img src="images/Narrenmuehle_ZH-CN5582540867/Narrenmuehle_ZH-CN5582540867_1280x768_test.jpg" width="400" height='300' title='1280x768'/>1280x768|
|4|<img src="images/Narrenmuehle_ZH-CN5582540867/Narrenmuehle_ZH-CN5582540867_768x1280_base.jpg" width="400" height='300' title='768x1280'/>768x1280|<img src="images/Narrenmuehle_ZH-CN5582540867/Narrenmuehle_ZH-CN5582540867_1024x768_test.jpg" width="400" height='300' title='1024x768'/>1024x768|
|5|<img src="images/Narrenmuehle_ZH-CN5582540867/Narrenmuehle_ZH-CN5582540867_768x1280_base.jpg" width="400" height='300' title='768x1280'/>768x1280|<img src="images/Narrenmuehle_ZH-CN5582540867/Narrenmuehle_ZH-CN5582540867_800x600_test.jpg" width="400" height='300' title='800x600'/>800x600|
|6|<img src="images/Narrenmuehle_ZH-CN5582540867/Narrenmuehle_ZH-CN5582540867_768x1280_base.jpg" width="400" height='300' title='768x1280'/>768x1280|<img src="images/Narrenmuehle_ZH-CN5582540867/Narrenmuehle_ZH-CN5582540867_800x480_test.jpg" width="400" height='300' title='800x480'/>800x480|
|7|<img src="images/Narrenmuehle_ZH-CN5582540867/Narrenmuehle_ZH-CN5582540867_768x1280_base.jpg" width="400" height='300' title='768x1280'/>768x1280|<img src="images/Narrenmuehle_ZH-CN5582540867/Narrenmuehle_ZH-CN5582540867_768x1280_test.jpg" width="400" height='300' title='768x1280'/>768x1280|
|8|<img src="images/Narrenmuehle_ZH-CN5582540867/Narrenmuehle_ZH-CN5582540867_768x1280_base.jpg" width="400" height='300' title='768x1280'/>768x1280|<img src="images/Narrenmuehle_ZH-CN5582540867/Narrenmuehle_ZH-CN5582540867_720x1280_test.jpg" width="400" height='300' title='720x1280'/>720x1280|
|9|<img src="images/Narrenmuehle_ZH-CN5582540867/Narrenmuehle_ZH-CN5582540867_768x1280_base.jpg" width="400" height='300' title='768x1280'/>768x1280|<img src="images/Narrenmuehle_ZH-CN5582540867/Narrenmuehle_ZH-CN5582540867_640x480_test.jpg" width="400" height='300' title='640x480'/>640x480|
|10|<img src="images/Narrenmuehle_ZH-CN5582540867/Narrenmuehle_ZH-CN5582540867_768x1280_base.jpg" width="400" height='300' title='768x1280'/>768x1280|<img src="images/Narrenmuehle_ZH-CN5582540867/Narrenmuehle_ZH-CN5582540867_480x800_test.jpg" width="400" height='300' title='480x800'/>480x800|
|11|<img src="images/Narrenmuehle_ZH-CN5582540867/Narrenmuehle_ZH-CN5582540867_768x1280_base.jpg" width="400" height='300' title='768x1280'/>768x1280|<img src="images/Narrenmuehle_ZH-CN5582540867/Narrenmuehle_ZH-CN5582540867_400x240_test.jpg" width="400" height='300' title='400x240'/>400x240|
|12|<img src="images/Narrenmuehle_ZH-CN5582540867/Narrenmuehle_ZH-CN5582540867_768x1280_base.jpg" width="400" height='300' title='768x1280'/>768x1280|<img src="images/Narrenmuehle_ZH-CN5582540867/Narrenmuehle_ZH-CN5582540867_320x240_test.jpg" width="400" height='300' title='320x240'/>320x240|
|13|<img src="images/Narrenmuehle_ZH-CN5582540867/Narrenmuehle_ZH-CN5582540867_768x1280_base.jpg" width="400" height='300' title='768x1280'/>768x1280|<img src="images/Narrenmuehle_ZH-CN5582540867/Narrenmuehle_ZH-CN5582540867_240x320_test.jpg" width="400" height='300' title='240x320'/>240x320|

结论：同一张图片利用图像原始全局直方图进行相似性判别时，当图片色彩变化相对平缓时，对不同分辨率的图片具有较高的准确性；当图片色彩变化相对剧烈时，对不同分辨率的图片相似性检测结果不太准确。

## 图像不同但相似的同分辨率和不同分辨率

- [图像不同但相似的同分辨率](2颜色直方图图像不同但相似同分辨率.csv)

|编号|图片名|分辨率|相似性检验结果|
|:-:|:-:|:-:|:-:|
|1|BeaujolaisRegion_ZH-CN1585928268	|1920x1080|0.969256|
|2|BeaujolaisRegion_ZH-CN1585928268	|1366x768|0.97246|
|3|BeaujolaisRegion_ZH-CN1585928268	|1280x768|0.975104|
|4|BeaujolaisRegion_ZH-CN1585928268	|1024x768|0.974003|
|5|BeaujolaisRegion_ZH-CN1585928268	|800x600|    0.982357|
|6|BeaujolaisRegion_ZH-CN1585928268	|800x480|    0.985964|
|7|BeaujolaisRegion_ZH-CN1585928268	|768x1280|0.982059|
|8|BeaujolaisRegion_ZH-CN1585928268	|720x1280|0.982247|
|9|BeaujolaisRegion_ZH-CN1585928268	|640x480|    0.929717|
|10|BeaujolaisRegion_ZH-CN1585928268|	480x800|    0.949163|
|11|BeaujolaisRegion_ZH-CN1585928268|	400x240|    0.955246|
|12|BeaujolaisRegion_ZH-CN1585928268|	320x240|    0.914007|
|13|BeaujolaisRegion_ZH-CN1585928268|	240x320|    0.924157|
  
|编号|原图|相似图|
|:-:|:-:|:-:|
|1|<img src="images/BeaujolaisRegion_ZH-CN1585928268/BeaujolaisRegion_ZH-CN1585928268_1920x1080_base.jpg" width="400" height='300' title='1920x1080'/>1920x1080|<img src="images/BeaujolaisRegion_ZH-CN1585928268/BeaujolaisRegion_ZH-CN1585928268_1920x1080_test.jpg" width="400" height='300' title='1920x1080'/>1920x1080|
|2|<img src="images/BeaujolaisRegion_ZH-CN1585928268/BeaujolaisRegion_ZH-CN1585928268_1366x768_base.jpg" width="400" height='300' title='1366x768'/>1366x768|<img src="images/BeaujolaisRegion_ZH-CN1585928268/BeaujolaisRegion_ZH-CN1585928268_1366x768_test.jpg" width="400" height='300' title='1366x768'/>1366x768|
|3|<img src="images/BeaujolaisRegion_ZH-CN1585928268/BeaujolaisRegion_ZH-CN1585928268_1280x768_base.jpg" width="400" height='300' title='1280x768'/>1280x768|<img src="images/BeaujolaisRegion_ZH-CN1585928268/BeaujolaisRegion_ZH-CN1585928268_1280x768_test.jpg" width="400" height='300' title='1280x768'/>1280x768|
|4|<img src="images/BeaujolaisRegion_ZH-CN1585928268/BeaujolaisRegion_ZH-CN1585928268_1024x768_base.jpg" width="400" height='300' title='1024x768'/>1024x768|<img src="images/BeaujolaisRegion_ZH-CN1585928268/BeaujolaisRegion_ZH-CN1585928268_1024x768_test.jpg" width="400" height='300' title='1024x768'/>1024x768|
|5|<img src="images/BeaujolaisRegion_ZH-CN1585928268/BeaujolaisRegion_ZH-CN1585928268_800x600_base.jpg" width="400" height='300' title='800x600'/>800x600|<img src="images/BeaujolaisRegion_ZH-CN1585928268/BeaujolaisRegion_ZH-CN1585928268_800x600_test.jpg" width="400" height='300' title='800x600'/>800x600|
|6|<img src="images/BeaujolaisRegion_ZH-CN1585928268/BeaujolaisRegion_ZH-CN1585928268_800x480_base.jpg" width="400" height='300' title='800x480'/>800x480|<img src="images/BeaujolaisRegion_ZH-CN1585928268/BeaujolaisRegion_ZH-CN1585928268_800x480_test.jpg" width="400" height='300' title='800x480'/>800x480|
|7|<img src="images/BeaujolaisRegion_ZH-CN1585928268/BeaujolaisRegion_ZH-CN1585928268_768x1280_base.jpg" width="400" height='300' title='768x1280'/>768x1280|<img src="images/BeaujolaisRegion_ZH-CN1585928268/BeaujolaisRegion_ZH-CN1585928268_768x1280_test.jpg" width="400" height='300' title='768x1280'/>768x1280|
|8|<img src="images/BeaujolaisRegion_ZH-CN1585928268/BeaujolaisRegion_ZH-CN1585928268_720x1280_base.jpg" width="400" height='300' title='720x1280'/>720x1280|<img src="images/BeaujolaisRegion_ZH-CN1585928268/BeaujolaisRegion_ZH-CN1585928268_720x1280_test.jpg" width="400" height='300' title='720x1280'/>720x1280|
|9|<img src="images/BeaujolaisRegion_ZH-CN1585928268/BeaujolaisRegion_ZH-CN1585928268_640x480_base.jpg" width="400" height='300' title='640x480'/>640x480|<img src="images/BeaujolaisRegion_ZH-CN1585928268/BeaujolaisRegion_ZH-CN1585928268_640x480_test.jpg" width="400" height='300' title='640x480'/>640x480|
|10|<img src="images/BeaujolaisRegion_ZH-CN1585928268/BeaujolaisRegion_ZH-CN1585928268_480x800_base.jpg" width="400" height='300' title='480x800'/>480x800|<img src="images/BeaujolaisRegion_ZH-CN1585928268/BeaujolaisRegion_ZH-CN1585928268_480x800_test.jpg" width="400" height='300' title='480x800'/>480x800|
|11|<img src="images/BeaujolaisRegion_ZH-CN1585928268/BeaujolaisRegion_ZH-CN1585928268_400x240_base.jpg" width="400" height='300' title='400x240'/>400x240|<img src="images/BeaujolaisRegion_ZH-CN1585928268/BeaujolaisRegion_ZH-CN1585928268_400x240_test.jpg" width="400" height='300' title='400x240'/>400x240|
|12|<img src="images/BeaujolaisRegion_ZH-CN1585928268/BeaujolaisRegion_ZH-CN1585928268_320x240_base.jpg" width="400" height='300' title='320x240'/>320x240|<img src="images/BeaujolaisRegion_ZH-CN1585928268/BeaujolaisRegion_ZH-CN1585928268_320x240_test.jpg" width="400" height='300' title='320x240'/>320x240|
|13|<img src="images/BeaujolaisRegion_ZH-CN1585928268/BeaujolaisRegion_ZH-CN1585928268_240x320_base.jpg" width="400" height='300' title='240x320'/>240x320|<img src="images/BeaujolaisRegion_ZH-CN1585928268/BeaujolaisRegion_ZH-CN1585928268_240x320_test.jpg" width="400" height='300' title='240x320'/>240x320|

- [图像不同但相似的不同分辨率](3颜色直方图图像不同但相似不同分辨率.csv)

|编号|图片名|分辨率|相似图分辨率|相似性检验结果|
|:-:|:-:|:-:|:-:|:-:|
|1|GodsGarden_ZH-CN3317703606     |768x1280	|1920x1080	|0.697619|
|2|GodsGarden_ZH-CN3317703606     |768x1280	|1366x768	|0.64564 |
|3|GodsGarden_ZH-CN3317703606     |768x1280	|1280x768	|0.63251 |
|4|GodsGarden_ZH-CN3317703606     |768x1280	|1024x768	|0.734612|
|5|GodsGarden_ZH-CN3317703606     |768x1280	|800x600	|0.731806|
|6|GodsGarden_ZH-CN3317703606     |768x1280	|800x480	|0.592676|
|7|GodsGarden_ZH-CN3317703606     |768x1280	|768x1280	|0.953649|
|8|GodsGarden_ZH-CN3317703606     |768x1280	|720x1280	|0.957368|
|9|GodsGarden_ZH-CN3317703606     |768x1280	|640x480	|0.703952|
|10|GodsGarden_ZH-CN3317703606     |768x1280	|480x800	|0.852223|
|11|GodsGarden_ZH-CN3317703606     |768x1280	|400x240	|0.51727 |
|12|GodsGarden_ZH-CN3317703606     |768x1280	|320x240	|0.572227|
|13|GodsGarden_ZH-CN3317703606     |768x1280	|240x320	|0.643358|

|编号|原图|相似图|
|:-:|:-:|:-:|
|1|<img src="images/GodsGarden_ZH-CN3317703606/GodsGarden_ZH-CN3317703606_768x1280_base.jpg" width="400" height='300' title='768x1280'/>768x1280|<img src="images/GodsGarden_ZH-CN3317703606/GodsGarden_ZH-CN3317703606_1920x1080_test.jpg" width="400" height='300' title='1920x1080'/>1920x1080|
|2|<img src="images/GodsGarden_ZH-CN3317703606/GodsGarden_ZH-CN3317703606_768x1280_base.jpg" width="400" height='300' title='768x1280'/>768x1280|<img src="images/GodsGarden_ZH-CN3317703606/GodsGarden_ZH-CN3317703606_1366x768_test.jpg" width="400" height='300' title='1366x768'/>1366x768|
|3|<img src="images/GodsGarden_ZH-CN3317703606/GodsGarden_ZH-CN3317703606_768x1280_base.jpg" width="400" height='300' title='768x1280'/>768x1280|<img src="images/GodsGarden_ZH-CN3317703606/GodsGarden_ZH-CN3317703606_1280x768_test.jpg" width="400" height='300' title='1280x768'/>1280x768|
|4|<img src="images/GodsGarden_ZH-CN3317703606/GodsGarden_ZH-CN3317703606_768x1280_base.jpg" width="400" height='300' title='768x1280'/>768x1280|<img src="images/GodsGarden_ZH-CN3317703606/GodsGarden_ZH-CN3317703606_1024x768_test.jpg" width="400" height='300' title='1024x768'/>1024x768|
|5|<img src="images/GodsGarden_ZH-CN3317703606/GodsGarden_ZH-CN3317703606_768x1280_base.jpg" width="400" height='300' title='768x1280'/>768x1280|<img src="images/GodsGarden_ZH-CN3317703606/GodsGarden_ZH-CN3317703606_800x600_test.jpg" width="400" height='300' title='800x600'/>800x600|
|6|<img src="images/GodsGarden_ZH-CN3317703606/GodsGarden_ZH-CN3317703606_768x1280_base.jpg" width="400" height='300' title='768x1280'/>768x1280|<img src="images/GodsGarden_ZH-CN3317703606/GodsGarden_ZH-CN3317703606_800x480_test.jpg" width="400" height='300' title='800x480'/>800x480|
|7|<img src="images/GodsGarden_ZH-CN3317703606/GodsGarden_ZH-CN3317703606_768x1280_base.jpg" width="400" height='300' title='768x1280'/>768x1280|<img src="images/GodsGarden_ZH-CN3317703606/GodsGarden_ZH-CN3317703606_1920x1080_test.jpg" width="400" height='300' title='1920x1080'/>1920x1080|
|8|<img src="images/GodsGarden_ZH-CN3317703606/GodsGarden_ZH-CN3317703606_768x1280_base.jpg" width="400" height='300' title='768x1280'/>768x1280|<img src="images/GodsGarden_ZH-CN3317703606/GodsGarden_ZH-CN3317703606_720x1280_test.jpg" width="400" height='300' title='720x1280'/>720x1280|
|9|<img src="images/GodsGarden_ZH-CN3317703606/GodsGarden_ZH-CN3317703606_768x1280_base.jpg" width="400" height='300' title='768x1280'/>768x1280|<img src="images/GodsGarden_ZH-CN3317703606/GodsGarden_ZH-CN3317703606_640x480_test.jpg" width="400" height='300' title='640x480'/>640x480|
|10|<img src="images/GodsGarden_ZH-CN3317703606/GodsGarden_ZH-CN3317703606_768x1280_base.jpg" width="400" height='300' title='768x1280'/>768x1280|<img src="images/GodsGarden_ZH-CN3317703606/GodsGarden_ZH-CN3317703606_480x800_test.jpg" width="400" height='300' title='480x800'/>480x800|
|11|<img src="images/GodsGarden_ZH-CN3317703606/GodsGarden_ZH-CN3317703606_768x1280_base.jpg" width="400" height='300' title='768x1280'/>768x1280|<img src="images/GodsGarden_ZH-CN3317703606/GodsGarden_ZH-CN3317703606_400x240_test.jpg" width="400" height='300' title='400x240'/>400x240|
|12|<img src="images/GodsGarden_ZH-CN3317703606/GodsGarden_ZH-CN3317703606_768x1280_base.jpg" width="400" height='300' title='768x1280'/>768x1280|<img src="images/GodsGarden_ZH-CN3317703606/GodsGarden_ZH-CN3317703606_320x240_test.jpg" width="400" height='300' title='320x240'/>320x240|
|13|<img src="images/GodsGarden_ZH-CN3317703606/GodsGarden_ZH-CN3317703606_768x1280_base.jpg" width="400" height='300' title='768x1280'/>768x1280|<img src="images/GodsGarden_ZH-CN3317703606/GodsGarden_ZH-CN3317703606_240x320_test.jpg" width="400" height='300' title='240x320'/>240x320|

结论：图像不同但相似的图片利用图像原始全局直方图进行相似性判别时，同分辨率下相似度检测结果准确性较高；不同分辨率下，相似度检测结果准确性低。

## [图像不同且不相似的同分辨率和不同分辨率](4颜色直方图不同图像不同分辨率和相同分辨率.csv)

|编号|图片1|图片2|分辨率1|分辨率2|相似性检验结果|
|:-:|:-:|:-:|:-:|:-:|:-:|
|1|PontFawr_ZH-CN1780190468	            |SynchronousFireflies_ZH-CN6323931412	|768x1280	|768x1280	|0.00634463|
|2|LionSurfing_ZH-CN7369892268	        |BaronLakes_ZH-CN7541190370          	|768x1280	|768x1280	|-0.00727522|
|3|WobblyBridge_ZH-CN7751845685	        |GriboyedovCanal_ZH-CN7887366015 	    |768x1280	|768x1280	|0.109737|
|4|StStephens_ZH-CN9373191410	        |Havasupai_ZH-CN0016003195              |768x1280	|768x1280	|0.155889|
|5|AdansoniaGrandidieri_ZH-CN1154912052	|MtBaldoSantuario_ZH-CN2301293454	    |768x1280	|768x1280	|0.0719352|
|6|PontFawr_ZH-CN1780190468	            |SynchronousFireflies_ZH-CN6323931412	|768x1280	|320x240	|-0.00261828|
|7|LionSurfing_ZH-CN7369892268	        |BaronLakes_ZH-CN7541190370	            |768x1280	|1280x768	|-0.0122369|
|8|WobblyBridge_ZH-CN7751845685	        |GriboyedovCanal_ZH-CN7887366015	    |768x1280	|1920x1080	|0.088117|
|9|StStephens_ZH-CN9373191410	        |Havasupai_ZH-CN0016003195	            |768x1280	|240x320	|0.193342|
|10|AdansoniaGrandidieri_ZH-CN1154912052|MtBaldoSantuario_ZH-CN2301293454	    |768x1280	|720x1280	|0.070701|

|编号|图片1|图片2|
|:-:|:-:|:-:|
|1|<img src="images/ColorHistTest4/PontFawr_ZH-CN1780190468_768x1280_base.jpg" width="400" height='300' title='768x1280'/>768x1280|<img src="images/ColorHistTest4/SynchronousFireflies_ZH-CN6323931412_768x1280_test.jpg" width="400" height='300' title='768x1280'/>768x1280|
|2|<img src="images/ColorHistTest4/LionSurfing_ZH-CN7369892268_768x1280_base.jpg" width="400" height='300' title='768x1280'/>768x1280|<img src="images/ColorHistTest4/BaronLakes_ZH-CN7541190370_768x1280_test.jpg" width="400" height='300' title='768x1280'/>768x1280|
|3|<img src="images/ColorHistTest4/WobblyBridge_ZH-CN7751845685_768x1280_base.jpg" width="400" height='300' title='768x1280'/>768x1280|<img src="images/ColorHistTest4/GriboyedovCanal_ZH-CN7887366015_768x1280_test.jpg" width="400" height='300' title='768x1280'/>768x1280|
|4|<img src="images/ColorHistTest4/StStephens_ZH-CN9373191410_768x1280_base.jpg" width="400" height='300' title='768x1280'/>768x1280|<img src="images/ColorHistTest4/Havasupai_ZH-CN0016003195_768x1280_test.jpg" width="400" height='300' title='768x1280'/>768x1280|
|5|<img src="images/ColorHistTest4/AdansoniaGrandidieri_ZH-CN1154912052_768x1280_base.jpg" width="400" height='300' title='768x1280'/>768x1280|<img src="images/ColorHistTest4/MtBaldoSantuario_ZH-CN2301293454_768x1280_test.jpg" width="400" height='300' title='768x1280'/>768x1280|
|6|<img src="images/ColorHistTest4/PontFawr_ZH-CN1780190468_768x1280_base.jpg" width="400" height='300' title='768x1280'/>768x1280|<img src="images/ColorHistTest4/SynchronousFireflies_ZH-CN6323931412_768x1280_test.jpg" width="400" height='300' title='768x1280'/>768x1280|
|7|<img src="images/ColorHistTest4/LionSurfing_ZH-CN7369892268_768x1280_base.jpg" width="400" height='300' title='768x1280'/>768x1280|<img src="images/ColorHistTest4/BaronLakes_ZH-CN7541190370_1280x768_test.jpg" width="400" height='300' title='1280x768'/>1280x768|
|8|<img src="images/ColorHistTest4/WobblyBridge_ZH-CN7751845685_768x1280_base.jpg" width="400" height='300' title='768x1280'/>768x1280|<img src="images/ColorHistTest4/GriboyedovCanal_ZH-CN7887366015_1920x1080_test.jpg" width="400" height='300' title='1920x1080'/>1920x1080|
|9|<img src="images/ColorHistTest4/StStephens_ZH-CN9373191410_768x1280_base.jpg" width="400" height='300' title='768x1280'/>768x1280|<img src="images/ColorHistTest4/Havasupai_ZH-CN0016003195_240x320_test.jpg" width="400" height='300' title='240x320'/>240x320|
|10|<img src="images/ColorHistTest4/AdansoniaGrandidieri_ZH-CN1154912052_768x1280_base.jpg" width="400" height='300' title='768x1280'/>768x1280|<img src="images/ColorHistTest4/MtBaldoSantuario_ZH-CN2301293454_720x1280_test.jpg" width="400" height='300' title='720x1280'/>720x1280|

结论：图像不同且不相似的同分辨率和不同分辨率的图像利用图像原始全局直方图进行相似性判别，无论分辨率是否相同，相似性检验结果都很低。



