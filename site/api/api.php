<?php

error_reporting(E_ERROR | E_PARSE | E_CORE_ERROR | E_COMPILE_ERROR);

$auth = [
  "host" => "127.0.0.1",
  "database" => "silicon",
  "login" => "sil",
  "password" => "password",
];

$executable = "";

$responce = [
  "status" => "error",
  "error" => "",
];

// $json = "{\"command\": \"GetUserInfo\", \"args\" : { \"bank_name\": \"bank1\", \"login\" : \"aaa\", \"password\" : \"12345\", \"account_id\" : 9}}";
// // echo $json;
// // echo "Local_Sil_Valley_Bank.exe -json \"" . str_replace("\"", "\\\"", $json) . "\"";
// $out2 = json_decode(shell_exec("Local_Sil_Valley_Bank.exe -json \"" . str_replace("\"", "\\\"", $json) . "\""));

// // echo print_r($out) . "<br/>";
// unset($out2->php_command);
// $out2->args = new stdClass;
// $out2->args->a = 12;

// echo json_encode($out2) . "<br/>";

$is_token_valid = false;
$token;
$bank_id = 0;
$user_id = 0;
$is_user_login = false;

$origin = null;

foreach (apache_request_headers() as $header => $key) {
  if ($header == 'Origin') {
    $origin = $key;
  }
}

try {
  if (!isset($_POST["json"])) {
    throw new Error("No JSON");
  }

  $request = json_decode($_POST["json"]);

  if ($request == null || $request->command == null) {
    throw new Error("Bad JSON");
  }

  $command = $request->command;

  $mysql = new mysqli($auth["host"], $auth["login"], $auth["password"], $auth["database"]);

  if ($mysql->connect_error != null) {
    throw new Error("Bad SQL");
  }

  if (isset($_COOKIE["token"])) {
    $token = $_COOKIE["token"];
    $stm = $mysql->prepare("SELECT user_id, bank_id, is_user_login FROM tokens WHERE token = ?");
    $stm->bind_param("s", $token);
    $stm->execute();
    $stm->store_result();

    if ($stm->num_rows != 0) {
      $is_token_valid = true;
      $stm->bind_result($user_id, $bank_id, $is_user_login);
      $stm->fetch();

      if (!isset($request->args)) {
        $request->args = new stdClass;
      }

      if ($is_user_login) {
        $request->args->user_id = $user_id;
      }
      $request->args->bank_id = $bank_id;
    }
  }

  if ($command == "NoToken") {
    $responce = [
      "status" => "success",
      "result" => []
    ];

    setcookie("token", $token, time() - 1, "/");
  }
  else if ($command == "GetStatus") {
    $responce = [
      "status" => "success",
      "result" => [
        "is_token" => false,
        "is_user" => false,
      ],
    ];

    if ($is_token_valid) {
      $responce["result"]["is_token"] = true;

      if($is_user_login) {
        $responce["result"]["is_user"] = true;
      }
      else {
        $responce["result"]["is_user"] = false;
      }
    }
    else {
      $responce["result"]["is_token"] = false;
    }
  }
  else if ($command == "Show_Banks") {
    $json = str_replace("\"", "\\\"", json_encode($request));
    $responce = json_decode(shell_exec("Local_Sil_Valley_Bank.exe -json \"" . $json . "\""));

    if (isset($responce->php_command)) {
      if (isset($responce->php_command->set)) {
        unset($responce->php_command->set);
      }
      unset($responce->php_command);
    }
  }
  else if ($command == "GetBank") {
    if ($is_token_valid) {
      $stm = $mysql->prepare("SELECT name, city FROM banks WHERE id = ?");
      $stm->bind_param("i", $bank_id);
      $stm->execute();
      $stm->bind_result($bank_name, $bank_city);
      $stm->fetch();
      $responce = [
        "status" => "success",
        "result" => [
          "name" => $bank_name,
          "city" => $bank_city,
        ],
      ];
    } else {
      $responce["error"] = "You even not select Bank >:(";
    }
  }
  else if ($command == "Select_Bank") {
    $json = str_replace("\"", "\\\"", json_encode($request));
    $responce = json_decode(shell_exec("Local_Sil_Valley_Bank.exe -json \"" . $json . "\""));

    if ($responce->status != "error") {
      if ($is_token_valid) {
        $stm = $mysql->prepare("UPDATE tokens SET bank_id = ?, is_user_login = false WHERE token = ?");
        $stm->bind_param("is", $responce->php_command->set, $token);
        $stm->execute();

        if ($stm->error != "") {
          $stm = $mysql->prepare("UPDATE tokens SET bank_id = ?, is_user_login = false WHERE token = ?");
          $stm->bind_param("is", $responce->php_command->set, $token);
          $stm->execute();
        }

        setcookie("token", $token, time() + 60*60*24*60, "/");
        $_COOKIE["token"] = $token;
        
        if (isset($responce->php_command)) {
          if (isset($responce->php_command->set)) {
            unset($responce->php_command->set);
          }
        }
      }
      else {
        $res = $mysql->query("SELECT SHA2(CONCAT(RANDOM_BYTES(100), id), 256) AS a FROM banks LIMIT 1");
        $token = $res->fetch_array(MYSQLI_ASSOC)["a"];

        $stm2 = $mysql->prepare("INSERT INTO tokens(token, bank_id) VALUES(?, ?)");
        $stm2->bind_param("si", $token, $responce->php_command->set);
        $stm2->execute();

        if ($stm->error != "") {
          $res = $mysql->query("SELECT SHA2(CONCAT(RANDOM_BYTES(100), id), 256) AS a FROM banks LIMIT 1");
          $token = $res->fetch_array(MYSQLI_ASSOC)["a"];

          $stm = $mysql->prepare("INSERT INTO tokens(token, bank_id) VALUES(?, ?)");
          $stm->bind_param("si", $token, $responce->php_command->set);
          $stm->execute();
        }

        setcookie("token", $token, time() + 60*60*24*60, "/");
        $_COOKIE["token"] = $token;
      }
    }
  } else if ($command == "Logout") {
    if ($is_token_valid) {
      if ($is_user_login) {
        $stm = $mysql->prepare("UPDATE tokens SET is_user_login = false WHERE token = ?");
        $stm->bind_param("s", $token);
        $stm->execute();
        $responce = [
          "status" => "success"
        ];

        setcookie("token", $token, time() + 60*60*24*60, "/");
      }
      else {
        throw new Error("You don't select user");
      }
    } else {
      throw new Error("You even not select Bank >:(");
    }
  }
  else if ($command == "AuthenticateUser") {
    $json = str_replace("\"", "\\\"", json_encode($request));
    $responce = json_decode(shell_exec("Local_Sil_Valley_Bank.exe -json \"" . $json . "\""));

    if ($is_token_valid) {
      if ($responce->status != "error") {
        $stm = $mysql->prepare("UPDATE tokens SET user_id = ?, is_user_login = true WHERE token = ?");
        $stm->bind_param("is", $responce->php_command->set, $token);
        $stm->execute();
  
        setcookie("token", $token, time() + 60*60*24*60, "/");
  
        if (isset($responce->php_command)) {
          if (isset($responce->php_command->set)) {
            unset($responce->php_command->set);
          }
        }
      }
    }
    else {
      $responce = [
        "status" => "error",
        "error" => "",
      ];
      throw new Error("You pass invalid token. DON'T HACK ME. >:(");
    }
  }
  else if ($command == "GetLogin") {
    if ($is_user_login) {
      $stm = $mysql->prepare("SELECT login FROM users WHERE user_id = ?");
      $stm->bind_param("i", $user_id);
      $stm->execute();
      $stm->bind_result($login_ff);
      $stm->fetch();
      $responce = [
        "status" => "success",
        "result" => [
          "login" => $login_ff,
        ],
      ];
    } else {
      $responce = [
        "status" => "error",
        "error" => ""
      ];
      throw new Error("You got log in.");
    }
  }
  else if ($command == "ChangeLogin") {
    if ($is_user_login) {
      $stm = $mysql->prepare("SELECT login FROM users WHERE user_id = ?");
      $stm->bind_param("i", $user_id);
      $stm->execute();
      $stm->bind_result($login_ff);
      $stm->fetch();

      $request->args->curr_login = $login_ff;
      $json = str_replace("\"", "\\\"", json_encode($request));
      $responce = json_decode(shell_exec("Local_Sil_Valley_Bank.exe -json \"" . $json . "\""));
    } else {
      $responce = [
        "status" => "error",
        "error" => ""
      ];
      throw new Error("You got log in.");
    }
  }
  else if ($command == "DeleteUser") {
    if ($is_user_login) {
      $json = str_replace("\"", "\\\"", json_encode($request));
      $responce = json_decode(shell_exec("Local_Sil_Valley_Bank.exe -json \"" . $json . "\""));

      setcookie("token", $token, time() - 1, "/");
    } else {
      $responce = [
        "status" => "error",
        "error" => ""
      ];
      throw new Error("You got log in.");
    }
  }
  else {
    if (!$is_token_valid) {
      throw new Error("You pass invalid token. DON'T HACK ME. >:(");
    }

    $json = str_replace("\"", "\\\"", json_encode($request));
    $responce = json_decode(shell_exec("Local_Sil_Valley_Bank.exe -json \"" . $json . "\""));

    if (isset($responce->php_command)) {
      if (isset($responce->php_command->set)) {
        unset($responce->php_command->set);
      }
    }

    setcookie("token", $token, time() + 60*60*24*60, "/");
  }

  $mysql->close();
}
catch (Error $err) {
  $responce["status"] = "error";
  $responce["error"] = $err->getMessage();
}

if ($origin != null) {
  header('Access-Control-Allow-Origin:' . $origin);
  header("Access-Control-Allow-Credentials: true");
}
header('Connection: close');
echo json_encode($responce);

?>