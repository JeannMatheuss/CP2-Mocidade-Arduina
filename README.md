### README

Este é um código para um sistema de monitoramento ambiental utilizando Arduino. O sistema é capaz de medir temperatura, umidade e intensidade de luz em um ambiente e exibir essas informações em um display LCD. Além disso, ele utiliza um sensor DHT11 para monitorar temperatura e umidade, um sensor LDR para medir a intensidade da luz e um LED RGB para indicar o estado do ambiente.

#### Componentes Utilizados:

- **Arduino Uno**: A placa de desenvolvimento utilizada como base para o projeto.
- **Sensor DHT11**: Sensor de temperatura e umidade digital.
- **Sensor LDR**: Sensor de luz para medir a intensidade luminosa do ambiente.
- **LED RGB**: Utilizado para indicar o estado do ambiente com cores diferentes.
- **Display LCD**: Para exibir as informações de temperatura, umidade e status do ambiente.
- **Buzzer**: Utilizado para emitir sons de alerta em determinadas condições.

#### Configurações e Funcionalidades:

1. **Inicialização do Sistema**: Ao ligar o sistema, um processo de inicialização é realizado, mostrando a logo da equipe "MOCIDADE ARDUINA" no display LCD.
2. **Monitoramento Contínuo**: O sistema monitora continuamente a temperatura, umidade e intensidade de luz no ambiente.
3. **Exibição no Display LCD**: As informações são exibidas no display LCD em intervalos regulares.
4. **Feedback Visual e Sonoro**:
   - A intensidade de luz é indicada pelo LED RGB, com cores diferentes representando diferentes condições de luminosidade.
   - O buzzer emite sons de alerta em casos de condições anormais, como temperatura ou umidade fora dos limites estabelecidos.
5. **Comunicação Serial**: O sistema também aceita entrada serial para definir uma cor específica para o LED RGB.

#### Funções Principais:

- **Luz**: Avalia a intensidade da luz no ambiente e realiza ações correspondentes, como acionar o LED RGB e emitir sons de alerta.
- **Umidade**: Monitora a umidade e fornece feedback visual e sonoro conforme os limites estabelecidos.
- **Temperatura**: Monitora a temperatura e fornece feedback visual e sonoro conforme os limites estabelecidos.

### Observações:

Certifique-se de que todos os componentes estejam corretamente conectados ao Arduino conforme especificado no código. As bibliotecas necessárias para o funcionamento do código devem estar instaladas no ambiente de desenvolvimento. Este código é fornecido como exemplo e pode ser modificado e expandido para atender às necessidades específicas do projeto.

#### Link da Simulação:

https://wokwi.com/projects/396823744224018433
![WhatsApp Image 2024-05-03 at 10 31 30](https://github.com/JeannMatheuss/CP2-Mocidade-Arduina/assets/111705820/38ccef60-a66d-4721-84f1-dfe9ad163ebb)





![WhatsApp Image 2024-05-03 at 10 31 31 (1)](https://github.com/JeannMatheuss/CP2-Mocidade-Arduina/assets/111705820/fc9b29eb-fa8c-425f-adf2-cf0592276230)
![WhatsApp Image 2024-05-03 at 10 31 31](https://github.com/JeannMatheuss/CP2-Mocidade-Arduina/assets/111705820/84865bff-13a2-43a0-a844-358dc5fbdb14)
