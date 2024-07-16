from tensorflow.keras.preprocessing.image import ImageDataGenerator
from tensorflow.keras.applications.mobilenet_v2 import preprocess_input
from tensorflow.keras.applications import MobileNetV2
from tensorflow.keras import Model, layers
from tensorflow.keras.callbacks import Callback
import time
import matplotlib.pyplot as plt
from PIL import Image
import numpy as np

# 資料目錄來源 以資料夾當作分類
src_dir = r'Datasets/DogandCat/'

# 使用ImageDataGenerator進行資料預處理
datagen = ImageDataGenerator(validation_split=0.2, preprocessing_function=preprocess_input) #validation_split用來指定訓練集的一定比例資料作為驗證集(每個epoch結束後測試模型)

# 建立訓練資料
train_generator = datagen.flow_from_directory(
    src_dir, target_size=(224, 224), batch_size=20, subset='training', class_mode='categorical')

# 建立驗證資料(flow_from_directory會自動掃描指定目錄中的子目錄，並將每個子目錄的名稱作為類別標籤)
valid_generator = datagen.flow_from_directory(
    src_dir, target_size=(224, 224), batch_size=20, subset='validation', class_mode='categorical')

# 建立MobileNetV2模型
mobilenetV2 = MobileNetV2(include_top=False, pooling='avg')
for layer in mobilenetV2.layers:
    layer.trainable = False

output = mobilenetV2.output
fc = layers.Dense(units=train_generator.num_classes, activation='softmax')(output)
model = Model(inputs=mobilenetV2.input, outputs=fc)

# 編譯模型
model.compile(loss='categorical_crossentropy', optimizer='Adam', metrics=['accuracy'])

# 訓練時間記錄回調函數
class TimeHistory(Callback):
    def on_train_begin(self, logs=None):
        self.times = []

    def on_epoch_begin(self, epoch, logs=None):
        self.epoch_time_start = time.time()

    def on_epoch_end(self, epoch, logs=None):
        self.times.append(time.time() - self.epoch_time_start)

time_callback = TimeHistory()

# 模型訓練
history = model.fit(
    train_generator,
    epochs=10,
    validation_data=valid_generator,
    callbacks=[time_callback]
)

# 訓練時間統計
print(f"Training times per epoch: {time_callback.times}")
print(f"Average training time per epoch: {np.mean(time_callback.times)} seconds")

# 性能估計：取得訓練和驗證的準確率和損失
acc = history.history['accuracy']
val_acc = history.history['val_accuracy']
loss = history.history['loss']
val_loss = history.history['val_loss']

# 繪製訓練和驗證的準確率和損失圖
epochs = range(len(acc))

plt.figure(figsize=(14, 5))

plt.subplot(1, 2, 1)
plt.plot(epochs, acc, 'bo', label='Training accuracy')
plt.plot(epochs, val_acc, 'b', label='Validation accuracy')
plt.title('Training and validation accuracy')
plt.legend()

plt.subplot(1, 2, 2)
plt.plot(epochs, loss, 'bo', label='Training loss')
plt.plot(epochs, val_loss, 'b', label='Validation loss')
plt.title('Training and validation loss')
plt.legend()

plt.show()

# 單次預測
def pred(img_path):
    img = preprocess_input(np.array(Image.open(img_path).convert('RGB').resize((224, 224))))    #將圖片調整大小至 (224, 224) 以符合 MobileNetV2 的輸入要求
    img = np.expand_dims(img, axis=0)   #將圖像從 (224, 224, 3) 變成 (1, 224, 224, 3) 
    result_prob = model.predict(img).tolist()[0]
    max_index = result_prob.index(max(result_prob))
    true_labels_dict = {v: k for k, v in train_generator.class_indices.items()} #將原本的value作為新字典的key，將原本的key作為新字典的value
    print(true_labels_dict[max_index], result_prob[max_index])

predict_img = 'Datasets/test1.png'
pred(predict_img)
