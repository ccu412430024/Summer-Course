from tensorflow.keras.applications.mobilenet_v2 import MobileNetV2, preprocess_input
from tensorflow.keras.preprocessing.image import ImageDataGenerator
from tensorflow.keras.callbacks import Callback
from tensorflow.keras import Model, layers
from PIL import Image
import numpy as np
import time
import matplotlib.pyplot as plt

# 資料目錄來源 以資料夾當作分類 , e.g. Datasets/cats, Datasets/dogs, ...
src_dir = r'Datasets/DogandCat/'
# 單次預測圖片
predict_img = r'Datasets/test1.png'

# 影像讀取處理
datagen = ImageDataGenerator(validation_split=0.2, preprocessing_function=preprocess_input)
train_generator = datagen.flow_from_directory(src_dir, target_size=(224, 224), batch_size=20, subset='training')
valid_generator = datagen.flow_from_directory(src_dir, target_size=(224, 224), batch_size=20, subset='validation')

# 模型建立
mobilenetV2 = MobileNetV2(include_top=False, pooling='avg')
for mlayer in mobilenetV2.layers:
    mlayer.trainable = False
mobilenetV2output = mobilenetV2.layers[-1].output
fc = layers.Dense(units=train_generator.num_classes, activation='softmax', name='custom_fc')(mobilenetV2output)
classification_model = Model(inputs=mobilenetV2.inputs, outputs=fc)
classification_model.compile(loss='categorical_crossentropy', optimizer='Adam', metrics=['accuracy'])

# 訓練時間記錄回調函數
class TimeHistory(Callback):
    def on_train_begin(self, logs={}):
        self.times = []

    def on_epoch_begin(self, epoch, logs={}):
        self.epoch_time_start = time.time()

    def on_epoch_end(self, epoch, logs={}):
        self.times.append(time.time() - self.epoch_time_start)

time_callback = TimeHistory()

# 模型訓練
history = classification_model.fit(train_generator, epochs=10, validation_data=valid_generator, callbacks=[time_callback])

# 訓練時間統計
times = time_callback.times
print(f"Training times per epoch: {times}")
print(f"Average training time per epoch: {np.mean(times)} seconds")

# 性能估計：繪製訓練和驗證的準確率和損失
acc = history.history['accuracy']
val_acc = history.history['val_accuracy']
loss = history.history['loss']
val_loss = history.history['val_loss']

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
true_labels_dict = {}
for key in train_generator.class_indices:
    true_labels_dict[train_generator.class_indices[key]] = key

def pred(img_path):
    img = preprocess_input(np.array(Image.open(img_path).convert('RGB')))
    img = np.array([img])
    result_prob = classification_model.predict(img).tolist()[0]
    max_index = result_prob.index(max(result_prob))
    print(true_labels_dict[max_index], result_prob[max_index])

pred(predict_img)
