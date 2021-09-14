

import cv2

print("Package Imported")



crackCascade = cv2.CascadeClassifier("haarcascades/haarcascade_crack_detection.xml")     # Provide the path for the cascade/trained model.



imgImported = cv2.imread("Small_Test_Sample/25.jpg")     # Input the path for the test image.
print(imgImported.shape)

imgGray = cv2.cvtColor(imgImported, cv2.COLOR_BGR2GRAY)     # Converting the colored test image into grayscale.

crackDetected = crackCascade.detectMultiScale(imgGray, 1.1, 5)     # Actually detecting the cracks here. The last two values are for "Scale" and "Minimum Neighbours".



for (x, y, width, height) in crackDetected:     # Looping through each of the detected cracks and drawing a bounding box around it.
    
    cv2.rectangle(imgImported, (x, y), (x + width, y + height), (255, 0, 0), 3)
      
    


cv2.imshow("Crack Detection - Hizbi@TactonBiotic", imgImported)     # Showing the final result image, with bounding boxes drawn on it.


          
cv2.waitKey(0)     # Wait infinitely, and don't close the result window.



