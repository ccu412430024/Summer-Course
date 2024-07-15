
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
model = LinearRegression()
model.fit(x.reshape(-1, 1), y)
y_pred = model.predict(x.reshape(-1, 1))

# 訓練誤差
train_error = mean_squared_error(y, y_pred)

# 3. 五折交叉驗證
kf = KFold(n_splits=5, shuffle=True, random_state=42)
cv_errors = []

for train_index, test_index in kf.split(x):
    x_train, x_test = x[train_index], x[test_index]
    y_train, y_test = y[train_index], y[test_index]
    model.fit(x_train.reshape(-1, 1), y_train)
    y_test_pred = model.predict(x_test.reshape(-1, 1))
    cv_errors.append(mean_squared_error(y_test, y_test_pred))

cv_error_mean = np.mean(cv_errors)

# 4. 視覺化
plt.scatter(x, y, color='blue', label='Data points')
plt.plot(x, y_pred, color='red', label='Fitted line')
plt.xlabel('x')
plt.ylabel('y')
plt.title('Linear Regression Fit')
plt.legend()
plt.show()

# 結果
print(f"Training Error: {train_error}")
print(f"5-Fold Cross-Validation Error: {cv_error_mean}")
