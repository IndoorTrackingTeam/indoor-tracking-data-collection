# Configuração do ESP32 no Arduino IDE

Este guia irá ajudá-lo a configurar o ESP32 no Arduino IDE e executar o código que se conecta a uma rede Wi-Fi, escaneia redes Wi-Fi próximas e envia os dados para uma API via HTTPS.

## Passo 1: Instalar o Arduino IDE

1. Faça o download e instale o [Arduino IDE](https://www.arduino.cc/en/software) no seu computador.

## Passo 2: Adicionar o Suporte para ESP32 no Arduino IDE

1. Abra o Arduino IDE.
2. Vá para `File` > `Preferences`.
3. No campo `Additional Boards Manager URLs`, adicione o seguinte URL: `https://dl.espressif.com/dl/package_esp32_index.json`
4. Clique em `OK` para salvar as configurações.

5. Vá para `Tools` > `Board` > `Boards Manager`.
6. Na janela que aparece, procure por `esp32`.
7. Selecione `esp32 by Espressif Systems` e clique em `Install`.

## Passo 3: Selecionar a Placa ESP32

1. Vá para `Tools` > `Board`.
2. Selecione o modelo da sua placa ESP32 na lista. Por exemplo, se estiver usando um ESP32 Dev Kit v1, selecione `ESP32 Dev Module`.

## Passo 4: Instalar as Bibliotecas Necessárias

1. Vá para `Sketch` > `Include Library` > `Manage Libraries`.
2. Na janela `Library Manager`, procure por `WiFi` e instale a biblioteca `WiFi` para ESP32.
3. Procure por `WiFiClientSecure` e instale a biblioteca `WiFiClientSecure`.

## Passo 5: Configurar o Código

1. Abra o codigo fornecido no Arduino IDE.

2. Substitua as variáveis `ssid`, `password` ne `esp_id` com as suas informações específicas.

## Passo 6: Selecionar a Porta Serial

1. Conecte o seu ESP32 ao computador usando um cabo USB.
2. Vá para `Tools` > `Port` e selecione a porta serial à qual o ESP32 está conectado.

## Passo 7: Fazer o Upload do Código

1. Clique no botão `Upload` (seta para a direita) no Arduino IDE para compilar e enviar o código para o ESP32.
2. Aguarde até que o processo de upload seja concluído. O ESP32 reiniciará e começará a executar o código.

## Passo 8: Monitorar a Saída Serial

1. Abra o Monitor Serial em `Tools` > `Serial Monitor` ou pressione `Ctrl+Shift+M`.
2. Defina a taxa de baud para `115200` para ver as mensagens de depuração.

Agora, o seu ESP32 está configurado e funcionando conforme o código fornecido. Ele se conectará à sua rede Wi-Fi, escaneará redes Wi-Fi próximas e enviará as informações para a API via HTTPS.