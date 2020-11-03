<?php

/*

	Problem koji rješava ovaj primjer je stvaranje veze na bazu podataka (MySQL) i dohvaćanje podataka koristeći različite ugrađene PHP funkcionalnosti.
	Srž LSP principa je u tome što se svaka od tih klasa može koristiti na mjestu bazne bez ikakvih problema u izvođenju rada.

*/

abstract class DatabaseManager {
	protected string $_server = "";
	protected string $_password = "";
	protected string $_username = "";
	protected string $_database = "";
	protected $_connection = null;
	
	abstract public function connect();
	abstract public function select(string $query);
	abstract public function disconnect();
	
	public function __construct(string $server, string $password, string $username, string $database) {
		$this->_server = $server;
		$this->_password = $password;
		$this->_username = $username;
		$this->_database = $database;
	}
}

class DatabaseManagerMySQLiObjectOriented extends DatabaseManager {
	public function connect() {
		$this->_connection = new mysqli($this->_server, $this->_username, $this->_password, $this->_database);
	}
	public function select(string $query) {
		return $this->_connection->query($query);
	}
	public function disconnect() {
		$this->_connection->close();
	}
}

class DatabaseManagerMySQLiProcedural extends DatabaseManager {
	public function connect() {
		$this->_connection = mysqli_connect($this->_server, $this->_username, $this->_password, $this->_database);
	}
	public function select(string $query) {
		return mysqli_query($this->_connection, $query);
	}
	public function disconnect() {
		mysqli_close($this->_connection);
	}
}

class DatabaseManagerPDO extends DatabaseManager {
	public function connect() {
		$this->_connection = new PDO("mysql:host=$this->_server;dbname=$this->_database", $this->_username, $this->_password);
		$this->_connection->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
	}
	public function select(string $query) {
		$stmt = $this->_connection->prepare($query);
		$stmt->execute();
		$result = $stmt->setFetchMode(PDO::FETCH_ASSOC);
		return $result;
	}
	public function disconnect() {
		$this->_connection = null;
	}
}

$db = new DatabaseManagerMySQLiObjectOriented("server", "password", "username", "database");
$db->connect();
$res = $db->select("SELECT * FROM users");
$db->disconnect();

?>