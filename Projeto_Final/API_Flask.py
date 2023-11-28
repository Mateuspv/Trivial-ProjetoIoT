from flask import Flask, request, jsonify, render_template
import psycopg2
from flask_cors import CORS

app = Flask(__name__, static_folder='templates', static_url_path='')
CORS(app)

db_host = "localhost"
db_database = "ProjetoFinal"
db_user = "postgres"
db_password = "1@jean"
db_port = "5432"

conn = psycopg2.connect(
    database = db_database,
    host = db_host,
    user = db_user,
    password = db_password,
    port = db_port,
    client_encoding="utf-8"
)


@app.route('/')
def index():
    return render_template('main.html')


@app.route('/get-sensor-data', methods=['GET'])
def post_data():
    print("Requisição recebida")
    umidade = request.args.get('umidade')
    validartroca = request.args.get('validartroca')
    tempoDesligamento = request.args.get('tempoDesligamento')
    ativadorTimer = request.args.get('ativadorTimer')


    if umidade is not None and validartroca is not None and tempoDesligamento is not None and ativadorTimer is not None:
        try:
            umidade = float(umidade)
            validartroca = float(validartroca)
            tempoDesligamento = float(tempoDesligamento)
            ativadorTimer = float(ativadorTimer)

            cur = conn.cursor()
            cur.execute("INSERT INTO sensor_data (umidade, validartroca, tempoDesligamento, ativadorTimer) VALUES (%s, %s, %s, %s)", (umidade, validartroca, tempoDesligamento, ativadorTimer))
            conn.commit()
            cur.close()

            return jsonify({'success': True}), 200
        except (ValueError, psycopg2.DatabaseError) as e:
            return jsonify({'error': 'Bad Request', 'message': str(e)}), 400
    else:
        return jsonify({'error': 'Missing data', 'message': 'All parameters are required'}), 400



@app.route('/get-validartroca', methods=['GET'])
def get_validartroca():
    try:
        # Recuperar dados do banco de dados
        cur = conn.cursor()
        cur.execute("select validartroca from sensor_data ORDER BY id DESC LIMIT 1")
        data = cur.fetchall()
        cur.close()

        return jsonify(data)
    except (ValueError, psycopg2.DatabaseError) as e:
            return jsonify({'error': 'Bad Request', 'message': str(e)}), 400

@app.route('/get-tempoDesligamento', methods=['GET'])
def get_tempoDesligamento():
    try:
        # Recuperar dados do banco de dados
        cur = conn.cursor()
        cur.execute("select tempoDesligamento from sensor_data ORDER BY id DESC LIMIT 1")
        data = cur.fetchall()
        cur.close()

        return jsonify(data)
    except (ValueError, psycopg2.DatabaseError) as e:
            return jsonify({'error': 'Bad Request', 'message': str(e)}), 400

@app.route('/get-umidade', methods=['GET'])
def get_umidade():
    try:
        # Recuperar dados do banco de dados
        cur = conn.cursor()
        cur.execute("select umidade from sensor_data ORDER BY id DESC LIMIT 1")
        data = cur.fetchall()
        cur.close()

        return jsonify(data)
    except (ValueError, psycopg2.DatabaseError) as e:
            return jsonify({'error': 'Bad Request', 'message': str(e)}), 400

@app.route('/get-ativadorTimer', methods=['GET'])
def get_ativadorTimer():
    try:
        # Recuperar dados do banco de dados
        cur = conn.cursor()
        cur.execute("select ativadorTimer from sensor_data ORDER BY id DESC LIMIT 1")
        data = cur.fetchall()
        cur.close()

        return jsonify(data)
    except (ValueError, psycopg2.DatabaseError) as e:
            return jsonify({'error': 'Bad Request', 'message': str(e)}), 400


if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000, debug=True)




    
 