import numpy as np
import matplotlib.pyplot as plt
import time
from sklearn.model_selection import KFold
from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_squared_error

# 1. 生成資料
# np.random.seed(42)  # 設置random seed以重現結果
rseed = np.random.seed(int(time.time()))    # 設置random seed
x = np.linspace(-5, 5, 30)  #生成從-5到5的30個均勻分布的數值
epsilon = np.random.normal(0, 1, x.shape)   #生成均值為0，標準差為1的常態分布noise
y = 2 * x + epsilon #線性關係

# 將資料分為訓練和測試兩部分
test_indices = np.arange(0, 15)  # 訓練資料索引
train_indices = np.arange(15, 30)  # 測試資料索引

x_train, x_test = x[train_indices], x[test_indices]
y_train, y_test = y[train_indices], y[test_indices]

# 2. 線性回歸分析
model = LinearRegression()  #初始化線性回歸模型
model.fit(x_train.reshape(-1, 1), y_train)  #用訓練資料x_train和y_train訓練模型
y_pred_train = model.predict(x_train.reshape(-1, 1))    #用訓練好的模型對x_train進行預測，得到預測值y_pred_train
y_pred_test = model.predict(x_test.reshape(-1, 1))  #用訓練好的模型對x_test進行預測，得到預測值y_pred_test

train_error = mean_squared_error(y_train, y_pred_train) # 訓練誤差(模型對於訓練資料集的平均誤差)
test_error = mean_squared_error(y_test, y_pred_test)    # 測試誤差(模型對於測試資料集的平均誤差)

# 3. 五折交叉驗證
kf = KFold(n_splits=5, shuffle=True, random_state=rseed)
cv_errors = []

for train_index, test_index in kf.split(x_train):
    x_train_cv, x_test_cv = x_train[train_index], x_train[test_index]
    y_train_cv, y_test_cv = y_train[train_index], y_train[test_index]
    model.fit(x_train_cv.reshape(-1, 1), y_train_cv)
    y_test_pred_cv = model.predict(x_test_cv.reshape(-1, 1))
    cv_errors.append(mean_squared_error(y_test_cv, y_test_pred_cv))

cv_error_mean = np.mean(cv_errors)

# 4. 視覺化
plt.figure(figsize=(10, 6))

# 顯示訓練和測試數據
plt.scatter(x_train, y_train, color='blue', label='TrainData')
plt.scatter(x_test, y_test, color='orange', label='TestData')

# 繪製回歸直線
x_full = np.concatenate((x_train, x_test))
y_full_pred = model.predict(x_full.reshape(-1, 1))
plt.plot(x_full, y_full_pred, color='green', label='Fitting Function')

plt.xlabel('X')
plt.ylabel('Y')
plt.title('Fitting Plot')
plt.legend()
plt.show()

# 結果
print(f"Training Error: {train_error}")
print(f"Test Error: {test_error}")
print(f"5-Fold Cross-Validation Error (on train data): {cv_error_mean}")
