
import numpy as np
import matplotlib.pyplot as plt
from sklearn.model_selection import KFold
from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_squared_error

# 1. 生成數據
np.random.seed(42)  # 設置random seed以重現結果
x = np.linspace(-5, 5, 30)  #生成從-5到5的30個均勻分布的數值
epsilon = np.random.normal(0, 1, x.shape)   #生成均值為0，標準差為1的常態分布noise
y = 2 * x + epsilon #線性關係

# 2. 線性回歸分析
model = LinearRegression()  #初始化線性回歸模型
model.fit(x.reshape(-1, 1), y)  #用生成的數據x和y訓練模型
y_pred = model.predict(x.reshape(-1, 1))    #用訓練好的模型對x進行預測，得到預測值y_pred

# 訓練誤差
train_error = mean_squared_error(y, y_pred) #計算訓練數據MSE

# 3. 五折交叉驗證
kf = KFold(n_splits=5, shuffle=True, random_state=42)   #初始化5折交叉驗證，其中數據在每次劃分時都被隨機打亂。
cv_errors = []  #空的list，用於存儲每次驗證的MSE

# 儲存每次交叉驗證的訓練和測試數據
x_train_all, y_train_all = [], []
x_test_all, y_test_all = [], []

for train_index, test_index in kf.split(x):
    x_train, x_test = x[train_index], x[test_index]
    y_train, y_test = y[train_index], y[test_index]
    x_train_all.append(x_train)
    y_train_all.append(y_train)
    x_test_all.append(x_test)
    y_test_all.append(y_test)
    model.fit(x_train.reshape(-1, 1), y_train)  #用訓練數據訓練模型
    y_test_pred = model.predict(x_test.reshape(-1, 1))  #用訓練好的模型對測試數據進行預測
    cv_errors.append(mean_squared_error(y_test, y_test_pred))   #計算測試數據的MSE，加到cv_errors

cv_error_mean = np.mean(cv_errors)  #計算5次交叉驗證MSE的平均值

# 4. 視覺化圖表
plt.figure(figsize=(10, 6))

# 顯示訓練數據
plt.scatter(x_train_all, y_train_all, color='blue', label='Train data')

# 顯示測試數據
plt.scatter(x_test_all, y_test_all, color='green', label='Test data')

plt.plot(x, y_pred, color='red', label='Fitted line')
plt.xlabel('x')
plt.ylabel('y')
plt.title('Linear Regression Fit')
plt.legend()
plt.show()

# 結果
print(f"Training Error: {train_error}")
print(f"5-Fold Cross-Validation Error: {cv_error_mean}")
