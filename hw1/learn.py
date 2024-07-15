from tensorflow.keras.preprocessing.image import ImageDataGenerator
from tensorflow.keras.applications.mobilenet_v2 import preprocess_input
from tensorflow.keras.applications import MobileNetV2
from tensorflow.keras import Model, layers
from tensorflow.keras.callbacks import Callback
import time
import matplotlib.pyplot as plt
from PIL import Image
import numpy as np

src_dir = r'Datasets/DogandCat/'
datagen = ImageDataGenerator(validation_split=0.2, preprocessing_function=preprocess_input)

train_generator = datagen.flow_from_directory(
    src_dir, target_size=(224, 224), batch_size=20, subset='training', class_mode='categorical')

valid_generator = datagen.flow_from_directory(
    src_dir, target_size=(224, 224), batch_size=20, subset='validation', class_mode='categorical')


mobilenetV2 = MobileNetV2(include_top=False, pooling='avg')
for layer in mobilenetV2.layers:
    layer.trainable = False

output = mobilenetV2.output
fc = layers.Dense(units=train_generator.num_classes, activation='softmax')(output)
model = Model(inputs=mobilenetV2.input, outputs=fc)
model.compile(loss='categorical_crossentropy', optimizer='Adam', metrics=['accuracy'])


class TimeHistory(Callback):
    def on_train_begin(self, logs=None):
        self.times = []

    def on_epoch_begin(self, epoch, logs=None):
        self.epoch_time_start = time.time()

    def on_epoch_end(self, epoch, logs=None):
        self.times.append(time.time() - self.epoch_time_start)

time_callback = TimeHistory()

history = model.fit(
    train_generator,
    epochs=10,
    validation_data=valid_generator,
    callbacks=[time_callback]
)

print(f"Training times per epoch: {time_callback.times}")
print(f"Average training time per epoch: {np.mean(time_callback.times)} seconds")


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


def pred(img_path):
    img = preprocess_input(np.array(Image.open(img_path).convert('RGB').resize((224, 224))))
    img = np.expand_dims(img, axis=0)
    result_prob = model.predict(img).tolist()[0]
    max_index = result_prob.index(max(result_prob))
    true_labels_dict = {v: k for k, v in train_generator.class_indices.items()}
    print(true_labels_dict[max_index], result_prob[max_index])

predict_img = 'Datasets/test1.png'
pred(predict_img)
