The assignment is all under one document, not to specs as most of the code is reused and is simpler to not repeat.
My IMU data computed with 100% accuracy across the board, except an occasional 95% total on the Decision tree model.
The sample size for the test was usually 9-11, or something one off that.

My IMU data had no bias or variance, as it was 100% accurate.

For my Audio data, the Logistic model had low change in the numbers from seed to seed. The decision tree varied wildy,
the Random Forest model did the best usually. A peak into one seed:
Logistic model
              precision    recall  f1-score   support

           0       0.80      0.67      0.73         6
           1       0.40      0.50      0.44         4
           2       0.67      0.50      0.57         4
           3       0.43      0.50      0.46         6

    accuracy                           0.55        20
   macro avg       0.57      0.54      0.55        20
weighted avg       0.58      0.55      0.56        20

Decision Tree model
              precision    recall  f1-score   support

           0       0.75      0.50      0.60         6
           1       0.40      0.50      0.44         4
           2       0.20      0.25      0.22         4
           3       0.50      0.50      0.50         6

    accuracy                           0.45        20
   macro avg       0.46      0.44      0.44        20
weighted avg       0.49      0.45      0.46        20

Random Forest model
 precision    recall  f1-score   support

           0       0.67      0.33      0.44         6
           1       0.33      0.50      0.40         4
           2       0.50      0.75      0.60         4
           3       0.80      0.67      0.73         6

    accuracy                           0.55        20
   macro avg       0.57      0.56      0.54        20
weighted avg       0.61      0.55      0.55        20

------------------------------------------------------------------------

The class IMU data shows similar results. Here are the statistics:
Logistic model
              precision    recall  f1-score   support

           0       0.65      0.80      0.72       152
           1       0.86      0.74      0.79       248

    accuracy                           0.76       400
   macro avg       0.75      0.77      0.75       400
weighted avg       0.78      0.76      0.76       400

Decision Tree model
              precision    recall  f1-score   support

           0       0.94      0.90      0.92       152
           1       0.94      0.96      0.95       248

    accuracy                           0.94       400
   macro avg       0.94      0.93      0.94       400
weighted avg       0.94      0.94      0.94       400

Random Forest model
              precision    recall  f1-score   support

           0       0.98      0.93      0.96       152
           1       0.96      0.99      0.97       248

    accuracy                           0.97       400
   macro avg       0.97      0.96      0.97       400
weighted avg       0.97      0.97      0.97       400

------------------------------------------------------------------------

For the class audio data, the logistic model was just barely below 40% accuracy, the other 2 were above 50%
Logistic model
              precision    recall  f1-score   support

           0       0.46      0.32      0.38       105
           1       0.27      0.25      0.26        96
           2       0.38      0.49      0.43        90
           3       0.44      0.49      0.47        89

    accuracy                           0.38       380
   macro avg       0.39      0.39      0.38       380
weighted avg       0.39      0.38      0.38       380

Decision Tree model
              precision    recall  f1-score   support

           0       0.56      0.60      0.58       105
           1       0.47      0.45      0.46        96
           2       0.47      0.50      0.48        90
           3       0.54      0.48      0.51        89

    accuracy                           0.51       380
   macro avg       0.51      0.51      0.51       380
weighted avg       0.51      0.51      0.51       380

Random Forest model
              precision    recall  f1-score   support

           0       0.63      0.72      0.68       105
           1       0.55      0.53      0.54        96
           2       0.61      0.57      0.59        90
           3       0.68      0.64      0.66        89

    accuracy                           0.62       380
   macro avg       0.62      0.62      0.62       380
weighted avg       0.62      0.62      0.62       380

Overall, the more data, the better the model did except for IMU. The Random forest was the best model with the 
lowest bias and variance. The decision tree tended to have low repeatability in its predictions.
The logistic model tended to do the worst.