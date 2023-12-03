from flask import Flask, request, jsonify, render_template
import psycopg2
from flask_cors import CORS

# Inicialização da aplicação Flask
app = Flask(__name__, static_folder='templates', static_url_path='')
CORS(app)

# Configuração do banco de dados PostgreSQL
db_host = "localhost"
db_database = "ProjetoFinal"
db_user = "postgres"
db_password = "postgres"
db_port = "5432"

# Conexão ao banco de dados
conn = psycopg2.connect(
    database=db_database,
    host=db_host,
    user=db_user,
    password=db_password,
    port=db_port,
    client_encoding="utf-8"
)

# Rota principal que renderiza a página HTML
@app.route('/')
def index():
    return render_template('main.html')

# Rota para receber dados do sensor e armazenar no banco de dados
@app.route('/get-sensor-data', methods=['GET'])
def post_data():
    print("Requisição recebida")
    umidade = request.args.get('umidade')
    validartroca = request.args.get('validartroca')
    tempoDesligamento = request.args.get('tempoDesligamento')
    ativadorTimer = request.args.get('ativadorTimer')

    if umidade is not None and validartroca is not None and tempoDesligamento is not None and ativadorTimer is not None:
        try:
            # Conversão para float e inserção no banco de dados
            umidade = float(umidade)
            validartroca = float(validartroca)
            tempoDesligamento = float(tempoDesligamento)
            ativadorTimer = float(ativadorTimer)

            cur = conn.cursor()
            cur.execute("INSERT INTO sensor_data (umidade, validartroca, tempoDesligamento, ativadorTimer) VALUES (%s, %s, %s, %s)",
                        (umidade, validartroca, tempoDesligamento, ativadorTimer))
            conn.commit()
            cur.close()

            return jsonify({'success': True}), 200
        except (ValueError, psycopg2.DatabaseError) as e:
            return jsonify({'error': 'Bad Request', 'message': str(e)}), 400
    else:
        return jsonify({'error': 'Missing data', 'message': 'All parameters are required'}), 400

# Rotas para recuperar dados de validacao da troca do banco de dados
@app.route('/get-validartroca', methods=['GET'])
def get_validartroca():
    try:
        cur = conn.cursor()
        cur.execute("SELECT validartroca FROM sensor_data ORDER BY id DESC LIMIT 1")
        data = cur.fetchall()
        cur.close()

        return jsonify(data)
    except (ValueError, psycopg2.DatabaseError) as e:
        return jsonify({'error': 'Bad Request', 'message': str(e)}), 400

# Rotas para recuperar dados de tempo de desligamento do banco de dados
@app.route('/get-tempoDesligamento', methods=['GET'])
def get_tempoDesligamento():
    try:
        cur = conn.cursor()
        cur.execute("SELECT tempoDesligamento FROM sensor_data ORDER BY id DESC LIMIT 1")
        data = cur.fetchall()
        cur.close()

        return jsonify(data)
    except (ValueError, psycopg2.DatabaseError) as e:
        return jsonify({'error': 'Bad Request', 'message': str(e)}), 400

# Rotas para recuperar dados de umidade do banco de dados
@app.route('/get-umidade', methods=['GET'])
def get_umidade():
    try:
        cur = conn.cursor()
        cur.execute("SELECT umidade FROM sensor_data ORDER BY id DESC LIMIT 1")
        data = cur.fetchall()
        cur.close()

        return jsonify(data)
    except (ValueError, psycopg2.DatabaseError) as e:
        return jsonify({'error': 'Bad Request', 'message': str(e)}), 400

# Rotas para recuperar dados de Ativar timer do banco de dados
@app.route('/get-ativadorTimer', methods=['GET'])
def get_ativadorTimer():
    try:
        cur = conn.cursor()
        cur.execute("SELECT ativadorTimer FROM sensor_data ORDER BY id DESC LIMIT 1")
        data = cur.fetchall()
        cur.close()

        return jsonify(data)
    except (ValueError, psycopg2.DatabaseError) as e:
        return jsonify({'error': 'Bad Request', 'message': str(e)}), 400

# Inicialização do servidor Flask
if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000, debug=True)