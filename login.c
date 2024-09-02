login()
{

	web_cleanup_cookies();
	web_cache_cleanup();
	web_cleanup_auto_headers();
	
	lr_think_time(10);
	
	lr_start_transaction("login_started_T001");

	web_set_sockets_option("SSL_VERSION", "AUTO");

	web_url("Catalog.action", 
		"URL=https://petstore.octoperf.com/actions/Catalog.action", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=", 
		"Snapshot=t7.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("login_started_T001", LR_AUTO);
	
	lr_rendezvous("LandingPage");

	/* *********************login********************* */
	
	lr_think_time(10);

	lr_start_transaction("login_SignIn_T002");

	web_url("Sign In", 
		"URL=https://petstore.octoperf.com/actions/Account.action;jsessionid=BE4A3989B8369427235F41549B74FE60?signonForm=", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=https://petstore.octoperf.com/actions/Catalog.action", 
		"Snapshot=t8.inf", 
		"Mode=HTML", 
		LAST);
	
	web_reg_find("Search=Body",
		"Text=Welcome ABC!",
		"SaveCount=T002Count",
		LAST);

	web_submit_data("Account.action", 
		"Action=https://petstore.octoperf.com/actions/Account.action", 
		"Method=POST", 
		"TargetFrame=", 
		"RecContentType=text/html", 
		"Referer=https://petstore.octoperf.com/actions/Account.action;jsessionid=BE4A3989B8369427235F41549B74FE60?signonForm=", 
		"Snapshot=t9.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=username", "Value=j2ee", ENDITEM, 
		"Name=password", "Value=j2ee", ENDITEM, 
		"Name=signon", "Value=Login", ENDITEM, 
		"Name=_sourcePage", "Value=Oka-L1HR1CNLOW2LxXP4gOyifeYZJ8ke15H9KCQR7ydetuBmkGzVmF-Cz7d2ojewb5hvaPcJJSGcp53tdRFgjowZ_0q-NvaARkGS070biYw=", ENDITEM, 
		"Name=__fp", "Value=_5VulaUo-KBL8xp2dy7ztIArk0ovJ6asZqGJIQCvJCZZF7c_w05D5f9iXHTyk8ua", ENDITEM, 
		LAST);
	
	if (atoi(lr_eval_string("{T002Count}")) > 0)
	{
		lr_end_transaction("login_SignIn_T002", LR_AUTO);
	}
	else
	{
		lr_end_transaction("login_SignIn_T002", LR_FAIL);
	}

	/* *********************logout********************* */
	
	
	
	web_reg_find("Search=Body",
		"Text=>Sign In<",
		"SaveCount=T003Count",
		LAST);
	
	lr_think_time(10);

	lr_start_transaction("login_SignOut_T003");

	web_url("Sign Out", 
		"URL=https://petstore.octoperf.com/actions/Account.action?signoff=", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=https://petstore.octoperf.com/actions/Catalog.action", 
		"Snapshot=t10.inf", 
		"Mode=HTML", 
		LAST);
	
	if (atoi(lr_eval_string("{T003Count}")) > 0)
	{
		lr_end_transaction("login_SignOut_T003", LR_AUTO);
	}
	else
	{
		lr_end_transaction("login_SignOut_T003", LR_FAIL);
	}
	
	

	iter ++;
	
	lr_log_message("Итерация номер-%d", iter);

	return 0;
}